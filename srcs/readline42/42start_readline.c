/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42start_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:30:34 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/15 21:44:11 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static int		parser(char *line)
{
	ft_putendl_fd(line, 1);
	// g_cmd = line;
	// g_cmd_size = ft_strlen(g_cmd);
	// ft_get_techline();
	// nullify();
	// ft_slice();
	return (0);
}

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
	
	signals_reroute();
	if (!isatty(STDIN_FILENO))
	{
		ft_putendl_fd("Something has happend", 2);
		return (1);
	}
	init_readline();
	if (set_noncanonical_input() == -1)
	{
		ft_putendl_fd("Terminal can't be changed", 2);
		ft_putendl_fd("Use non-interactive shell", 2);
		return (1);
	}
	init_prompt(flag, end, send);
	termtype = getenv("TERM");
	termtype = (termtype == NULL) ? "xterm-256color" : termtype;
	tmp = tgetent(room_termtype, termtype);
	if (start_readline42(tmp))
		return (1);
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
			ft_putendl_fd("Something has happend", 2);
			return (1);
		}
	if (!(cmd = readline()))
	{
		ft_putendl_fd("Something has happend", 2);
		return (1);
	}
	if (reset_canonical_input())
		exit(1);
	cmd = finalize_cmd(cmd);
	clean_readline42();
	if (parser(cmd))
		return (1);
	return (0);
}

char			*finalize_cmd(char *cmd)
{
	char		*sign;
	char		*tmp;
	char		*final;

	if ((sign = ft_strchr(cmd, '#')) != NULL)
	{
		tmp = ft_strndup(cmd, sign - cmd);
		final = ft_strtrim(tmp);
		free(tmp);
	}
	else
		final = ft_strtrim(cmd);
	free(cmd);
	return (final);
}


int				clean_readline42(void)
{
	//выходя из ридлайна;
	//t_completion,t_rline,  
	return (0);
}

