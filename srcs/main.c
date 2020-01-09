/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 15:54:55 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/09 14:12:19 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static int	options(int argc, char **argv)
{
	if (argc == 2 && ft_strcmp(argv[1], "--readline") == 0)
	{
		print_help(2);
		return (0);
	}
	if (argc == 2 && ft_strcmp(argv[1], "--simple") == 0)
	{
		print_help(3);
		return (0);
	}
	return (1);
}

static int	finalize_cmd(char *cmd)
{
	char	*sign;
	char	*tmp;
	char	*final;

	if ((sign = ft_strchr(cmd, '#')) != NULL)
	{
		tmp = ft_strndup(cmd, sign - cmd);
		final = ft_strtrim(tmp);
		free(tmp);
	}
	else
		final = ft_strtrim(cmd);
	free(cmd);
	ft_putendl_fd(final, 1);
	free(final);
	return (0);
}

/*
** We take default xterm-256color - terminal
*/

int			main(int argc, char **argv)
{
	char	*cmd;
	char	*termtype;
	char	room_termtype[2];
	
	//сделать вход для heredoc, кавычек и экранирования. В этих случаях
	// не выводится промпт
	if (options(argc, argv) == 0)
		return (0);
	if (isatty(STDIN_FILENO))
	{
		termtype = getenv("TERM");
		if (termtype == NULL)
			termtype = "xterm-256color";
		if (tgetent(room_termtype, termtype) != 1)
			if (!(cmd = readline_simple()))
			{
				ft_putendl_fd("Something has happend", 2);
				return (1);
			}
	}
	if (!(cmd = readline()))
	{
		ft_putendl_fd("Something has happend", 2);
		return (1);
	}
	finalize_cmd(cmd);
	make_ctrl_y(2, NULL);
	return (0);
}
