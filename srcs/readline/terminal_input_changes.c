#include "shell42.h"
#include "readline.h"

/*
** Here we check the terminal (we already know that
** our group owns a controlling terminal) and set it
** to the non-canonical mode
*/

int					check_terminal(void)
{
	if (!isatty(STDIN_FILENO) || mf_protection())
	{
		error_handler(TERMINAL_EXISTS, NULL);
		free(g_rline.cmd);
		clean_everything();
		exit(TERMINAL_EXISTS);
	}
	if (set_noncanonical_input() == -1)
	{
		error_handler(TERMINAL_TO_NON, NULL);
		free(g_rline.cmd);
		clean_everything();
		exit(TERMINAL_TO_NON);
	}
	return (0);
}

/*
** Protects the 0-stream after programs that could have changed
** it to NONBLOCK
** For example, nvim (neovim) does that so after launching it in
** background without mf_protections - there will be no stop on
** read and we will come back to the same read and so on - 
** dead loop
** Mf = "modify fd" or motherfucker (historically)
*/

int					mf_protection(void)
{
	int				flags;
	int				tmp;

	flags = fcntl(STDIN_FILENO, F_GETFL, 0);
	if (flags < 0)
		return (-1);
	tmp = fcntl(STDIN_FILENO, F_SETFL, flags & ~(O_NONBLOCK));
	return ((tmp < 0) ? -1 : 0);
}

/*
** Here we change canonical mode to the non-canonical one
** where we are able to control the input, by turning off the
** ECHO flag, we start to control the console frontend as well
** ISIG flag should not be turned off to continue to catch
** signals (otherwise SIGWINCH) will also be inavailable
*/

int					set_noncanonical_input(void)
{
	struct termios	tty;

	if (tcgetattr(STDIN_FILENO, &tty) < 0)
		return (-1);
	g_backup_tty = tty;
	tty.c_lflag &= ~(ICANON | ECHO);
	tty.c_cc[VMIN] = 1;
	tty.c_cc[VTIME] = 1;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &tty) < 0)
		return (-1);
	if (tcgetattr(STDIN_FILENO, &tty) < 0 ||
			((tty.c_lflag & (ICANON | ECHO) ||
			tty.c_cc[VMIN] != 1 || tty.c_cc[VTIME] != 1)))
		reset_canonical_input();
	return (0);
}

int					reset_canonical_input(void)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &g_backup_tty) != 0)
	{
		error_handler(TERMINAL_TO_CAN, NULL);
		exit(TERMINAL_TO_CAN);
	}
	return (0);
}

int					init_terminal_screen(void)
{
	if (ioctl(1, TIOCGWINSZ, &g_screen))
	{
		error_handler(TERMINAL_EXISTS, NULL);
		free(g_rline.cmd);
		clean_everything();
		exit(TERMINAL_EXISTS);
	}
	if (g_screen.ws_col == 0)
		g_screen.ws_col = DEFAULT_SCREEN_SIZE;
	return (0);
}


// int						back_to_noncanonical_input(void) //TODO убрать?
// {
// 	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_tty) < 0)
// 		return (-1);
// 	if (tcgetattr(STDIN_FILENO, &g_tty) < 0 ||
// 		((g_tty.c_lflag & (ICANON | ECHO) ||
// 		g_tty.c_cc[VMIN] != 1 || g_tty.c_cc[VTIME] != 1)))
// 		reset_canonical_input();
// 	return (0);
// }
