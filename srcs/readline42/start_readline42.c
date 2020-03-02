/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_readline42.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:30:34 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/02 12:47:28 by sschmele         ###   ########.fr       */
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
	char		room_termtype[100];
	int			tmp;

	start_history();
	signal(SIGWINCH, sig_screen);
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
			clean_readline42();
			clean_everything();
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
	char		*final;

	if (tmp != 1)
		readline_simple();
	else
		readline();
	reset_canonical_input();
	check_menu();
	final = finalize_cmd(g_rline.cmd);
	clean_readline42();
	signals_reroute(2);
	parser(final);
	return (0);
}

char			*finalize_cmd(char *cmd)
{
	char		*out;

	if (g_rline.cmd_len == 0)
	{
		out = ft_strdup(cmd);
	}
	else
	{
		out = ft_strjoin(cmd, "\n");
	}
	return (out);
}
