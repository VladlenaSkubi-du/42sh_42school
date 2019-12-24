/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 15:54:55 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/24 16:56:49 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

/*
** We take default xterm-256color - terminal
*/

int			main(int argc, char **argv)
{
	char	*cmd;
	char	*termtype;
	char	room_termtype[2];
	size_t	pos_old;

	//сделать вход для heredoc, кавычек и экранирования. В этих случаях
	// не выводится промпт
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
	make_ctrl_y(2, NULL);
	if (g_rline.pos > 0)
	{
		pos_old = g_rline.pos;
		g_rline.pos = ft_strlen(g_rline.cmd);
		if (move_cursor_from_old_position(pos_old, 'r'))
			return (1);
	}
	printf("\n%s\n", cmd);
	free(cmd);
	return (0);
}
