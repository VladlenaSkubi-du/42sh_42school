/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_input_changes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:17:13 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/16 19:06:39 by sschmele         ###   ########.fr       */
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
		reset_canonical_input();
	return (0);
}

int				reset_canonical_input(void)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &g_backup_tty) != 0)
	{
		error_handler(TERMINAL_TO_CAN, NULL);
		exit(TERMINAL_TO_CAN);
	}
	return (0);
}

int				back_to_noncanonical_input(void) //TODO если не станем нигде использовать, убрать
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_tty) < 0)
		return (-1);
	if (tcgetattr(STDIN_FILENO, &g_tty) < 0 ||
		((g_tty.c_lflag & (ICANON | ECHO) ||
		g_tty.c_cc[VMIN] != 1 || g_tty.c_cc[VTIME] != 1)))
		reset_canonical_input();
	return (0);
}
