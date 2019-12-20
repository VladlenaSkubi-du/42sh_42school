/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_changes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:51:01 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/20 12:59:00 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** The main functionality starts from here, because we need to reset the
** terminal mode
** By "tcgetattr(STDIN_FILENO, &tty) < 0" we check if all the changes
** were launched.
*/

int				terminal_init_start(int argc, char **argv)
{
	char			*result;

	if (tcgetattr(STDIN_FILENO, &g_tty) < 0)
		return (-1);
	g_backup_tty = g_tty;
	g_tty.c_lflag &= ~(ICANON | ECHO);
	g_tty.c_cc[VMIN] = 1;
	g_tty.c_cc[VTIME] = 1;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_tty) < 0)
		exit(1);
	if (tcgetattr(STDIN_FILENO, &g_tty) < 0 ||
		((g_tty.c_lflag & (ICANON | ECHO) ||
		g_tty.c_cc[VMIN] != 1 || g_tty.c_cc[VTIME] != 1)))
	{
		reset_canonical_input();
		return (-1);
	}
	redirect_signals();
	result = main_start_selection(argc, (const char**)argv);
	reset_canonical_input();
	(result != NULL) ? ft_putendl_fd(result, 1) : ft_putchar_fd('\n', 1);
	free(result);
	return (0);
}

void			reset_canonical_input(void)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &g_backup_tty) != 0)
	{
		ft_putstr_fd("Can't change terminal back. ", 2);
		ft_putendl_fd("You should reset the terminal", 2);
		exit(1);
	}
}

void			back_to_noncanonical_input(void)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_tty) < 0)
		exit(1);
	if (tcgetattr(STDIN_FILENO, &g_tty) < 0 ||
		((g_tty.c_lflag & (ICANON | ECHO) ||
		g_tty.c_cc[VMIN] != 1 || g_tty.c_cc[VTIME] != 1)))
	{
		reset_canonical_input();
		exit(1);
	}
}

/*
** "tgetstr("ti", &buffer)" - function changes the pointer of buffer;
** `ti' - String of commands to put the terminal into whatever special
** modes are needed or appropriate for programs that move the cursor
** nonsequentially around the screen;
** `vi' - String to make the cursor invisible;
** `cl' - String to clear the entire screen and
** put cursor at upper left corner;
*/

void			make_fullscreen(void)
{
	char		buf[30];
	char		*buffer;

	buffer = buf;
	tputs(tgetstr("ti", &buffer), 1, ft_putint);
	tputs(tgetstr("vi", &buffer), 1, ft_putint);
	buffer = buf;
	clean_screen();
}

/*
** "tgetstr("ti", &buffer)" - function changes the pointer of buffer;
** `te' - String to return terminal to settings for sequential output;
** `ve' - String to return the cursor to normal.
*/

void			reset_terminal_mode(void)
{
	char		buf[50];
	char		*buffer;

	buffer = buf;
	tputs(tgetstr("ve", &buffer), 1, ft_putint);
	tputs(tgetstr("te", &buffer), 1, ft_putint);
	buffer = buf;
}
