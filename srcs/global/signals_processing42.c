#include "shell42.h"
#include "readline.h"

int					signals_reroute(int from)
{
	if (from == 1)
	{
		signal(SIGINT, signal_ctrl_c_readline);
		signal(SIGWINCH, signal_screen_readline);
		signal(SIGCONT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
	}
	else if (from == 2)
	{
		signal(SIGINT, signal_ctrl_c_parser);
		signal(SIGWINCH, SIG_DFL);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGCONT, SIG_IGN);
	}
	return (0);
}

void				signal_ctrl_c_readline(int sig)
{
	check_after_line();
	ft_putchar_fd('\n', STDOUT_FILENO);
	g_prompt.prompt_func = main_prompt;
	g_prompt.prompt_func();
	ft_bzero(g_rline.cmd, g_rline.cmd_buff_len);
	g_rline.cmd_len = 0;
	g_rline.pos = 0;
	g_rline.pos_x = g_prompt.prompt_len;
	if (g_prompt.prompt_len >= g_screen.ws_col)
		g_rline.pos_x = g_prompt.prompt_len % g_screen.ws_col;
	g_rline.pos_y = 0;
	g_rline.str_num = 1;
	g_rline.flag = 0;
}

void				signal_screen_readline(int sig) //REWRITE! VLADA
{
	check_after_line();
	front_set_cursor_jmp(&g_rline.pos, &g_rline.pos_x, &g_rline.pos_y, 1);
	move_cursor_from_old_position(0, 'l');
	position_cursor("ch", 0, 0);
	tputs(g_cap.cd, 1, printc);
	ioctl(1, TIOCGWINSZ, &g_screen);
	g_prompt.prompt_func();
	if (g_prompt.prompt_len >= g_screen.ws_col)
		g_rline.pos_x = g_prompt.prompt_len % g_screen.ws_col;
	front_insert_cmd_till_the_end(g_rline.pos_y + 1);
}

void				signal_ctrl_c_parser(int sig)
{
	ft_putendl_fd("\nstopped by signal SIGINT", STDOUT_FILENO);
}