/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_readline42.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:30:34 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/05 15:19:30 by sschmele         ###   ########.fr       */
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
		if (start_readline42(tmp))
			return (1);
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
		cmd = readline_simple();
	else
		cmd = readline();
	reset_canonical_input();
	cmd = finalize_cmd(cmd);
	clean_readline42();
	signals_reroute(2);
	if (parser(cmd))
		return (1); //TODO erro
	return (0);
}

char			*finalize_cmd(char *cmd)
{
	char		*sign;
	char		*tmp;
	char		*final;

	check_menu();
	final = NULL;
	if (cmd == NULL)
		return (final);
	if (g_rline.cmd_len == 0)
		return (NULL);
	if ((sign = ft_strchr(cmd, '#')) != NULL)
	{
		tmp = ft_strndup(cmd, sign - cmd);
		final = ft_strtrim(tmp);
		free(tmp);
		return (final);
	}
	if (g_rline.cmd_len > 0)
		final = ft_strtrim(cmd);
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