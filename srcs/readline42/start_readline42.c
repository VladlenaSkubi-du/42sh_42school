/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_readline42.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:30:34 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/07 13:31:03 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "shell42.h"

/*
** @flag = 'm' - main_prompt
**          = 'h' - heredoc
**          = 'd' = dquote
**			= 's' = subshell
**			= 'o' = other
*/

int				interactive_shell(void)
{
	char		*termtype;
	char		room_termtype[2];
	int			tmp;

	start_history();
	while (1)
	{
		init_readline();
		if (!isatty(STDIN_FILENO))
		{
			error_handler(TERMINAL_EXISTS, NULL);
			exit(TERMINAL_EXISTS);
		}
		if (set_noncanonical_input() == -1)
		{
			error_handler(TERMINAL_TO_NON, NULL);
			exit(TERMINAL_TO_NON);
		}
		g_prompt.prompt_func();
		termtype = getenv("TERM");
		termtype = (termtype == NULL) ? "xterm-256color" : termtype;
		tmp = tgetent(room_termtype, termtype);
		start_readline42(tmp);
	}
	return (0);
}

/*
** We take default xterm-256color - terminal
*/

int				start_readline42(int tmp)
{
	char		*cmd;

	if (tmp != 1)
		readline_simple();
	else
		readline();
	reset_canonical_input();
	check_menu();
	cmd = finalize_cmd(g_rline.cmd);
	clean_readline42();
	signals_reroute(2);
	parser(cmd);
	return (0);
}

char			*finalize_cmd(char *cmd)
{
	char		*final;
	
	// final = NULL;
	
	// if (g_rline.cmd_len == 0)
	// 	return (ft_strdup("\n")); //иначе лишние переносы строки в строке!
	if (g_rline.cmd_len == 0)
		return (ft_strdup(cmd));
	final = ft_strjoin(cmd, "\n"); // тоже хз зачем тут \n добавлять
	return (final);
}

int				init_prompt(char flag)
{
	if (flag == 'm')
		g_prompt.prompt_func = main_prompt;
	else if (flag == 'd')
		g_prompt.prompt_func = dquote_prompt;
	else if (flag == 'h')
		g_prompt.prompt_func = heredoc_prompt;
	else if (flag == 'o')
		g_prompt.prompt_func = other_prompt;
	g_prompt.prompt_func();
	return (0);
}