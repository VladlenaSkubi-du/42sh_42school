/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_readline42.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:30:34 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/21 20:27:42 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

/*
** @flag = 'm' - main_prompt
**          = 'h' - heredoc
**          = 'q' = dquote
*/

int				interactive_shell(char flag, char end, char *send)
{
	char		*termtype;
	char		room_termtype[2];
	int			tmp;

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
		init_prompt(flag, send);
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
		if (!(cmd = readline_simple()))
		{
			ft_putendl_fd("Something has happend", 2); //TODO error
			return (1);
		}
	if (!(cmd = readline()))
	{
		ft_putendl_fd("Something has happend", 2); //TODO error
		return (1);
	}
	reset_canonical_input();
	cmd = finalize_cmd(cmd);
	clean_readline42();
	signals_reroute(2);
	if (parser(cmd))
		return (1); //TODO error
	return (0);
}

char			*finalize_cmd(char *cmd)
{
	char		*sign;
	char		*tmp;
	char		*final;

	final = NULL;
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
