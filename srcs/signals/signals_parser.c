#include "shell42.h"

void				signal_ctrl_c_parser(int sig)
{
	ft_putendl_fd("\nstopped by signal SIGINT", STDOUT_FILENO);
}

void				signal_ctrl_z_parser(int sig)
{
	ft_putendl_fd("\nSIGSTP, to do", STDOUT_FILENO);
}

void				signal_ctrl_bslash_parser(int sig)
{
	ft_putendl_fd("\nSIGQUIT, to do", STDOUT_FILENO);
}

void				signal_ctrl_y_parser(int sig)
{
	ft_putendl_fd("\nSIGCONT, to do", STDOUT_FILENO);
}