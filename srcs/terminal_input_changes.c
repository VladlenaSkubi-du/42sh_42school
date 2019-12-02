/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_input_changes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:17:13 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/02 15:03:47 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int				set_noncanonical_input(void)
{
	if (tcgetattr(STDIN_FILENO, &g_tty) < 0)
		return (-1);
	g_backup_tty = g_tty;
	g_tty.c_lflag &= ~(ICANON | ECHO);
	g_tty.c_cc[VMIN] = 1;
	g_tty.c_cc[VTIME] = 1;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_tty) < 0)
		return (-1);
	if (tcgetattr(STDIN_FILENO, &g_tty) < 0 ||
		((g_tty.c_lflag & (ICANON | ECHO) ||
		g_tty.c_cc[VMIN] != 1 || g_tty.c_cc[VTIME] != 1)))
	{
		if (reset_canonical_input() < 0)
			exit(1);
		return (-1);
	}
	return (0);
}

int				reset_canonical_input(void)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &g_backup_tty) != 0)
	{
		ft_putstr_fd("Can't change terminal back. ", 2);
		ft_putendl_fd("You should reset the terminal", 2);
		return (-1);
	}
	return (0);
}

int				back_to_noncanonical_input(void)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_tty) < 0)
		return (-1);
	if (tcgetattr(STDIN_FILENO, &g_tty) < 0 ||
		((g_tty.c_lflag & (ICANON | ECHO) ||
		g_tty.c_cc[VMIN] != 1 || g_tty.c_cc[VTIME] != 1)))
	{
		if (reset_canonical_input() < 0)
			exit(1);
		return (-1);
	}
	return (0);
}