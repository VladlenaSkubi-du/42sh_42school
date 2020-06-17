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
	if (g_rline.flag & AFTER_LINE_HIST)
	{
		position_cursor("ch", 0, 0);
		tputs(g_cap.cd, 1, printc);
		g_rline.flag &= ~AFTER_LINE_HIST;
	}
	else
	{
		check_after_line();
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	g_prompt.prompt_func = main_prompt;
	g_prompt.prompt_func();
	if (g_rline.cmd[0])
		ft_bzero(g_rline.cmd, g_rline.cmd_buff_len);
	g_rline.cmd_len = 0;
	g_rline.pos = 0;
	g_rline.pos_x = count_prompt_len();
	g_rline.pos_y = 0;
	g_rline.str_num = 1;
	g_rline.flag = 0;
}

void				signal_screen_readline(int sig)
{
	int				i;

	check_after_line();
	position_cursor("ch", 0, 0);
	tputs(g_cap.cd, 1, printc);
	if (ioctl(1, TIOCGWINSZ, &g_screen))
	{
		error_handler(TERMINAL_EXISTS, NULL);
		clean_everything();
		exit(TERMINAL_EXISTS);
	}
	g_rline.pos = 0;
	g_rline.pos_x = count_prompt_len();
	g_rline.pos_y = 0;
	g_rline.str_num = 1;
	g_prompt.prompt_func();
	i = -1;
	while (g_rline.cmd[++i])
	{
		g_rline.pos++;
		front_insert_one_char(g_rline.cmd[i],
			g_rline.pos_y, 'm', NULL);
	}
		
}

void				signal_ctrl_c_parser(int sig)
{
	ft_putendl_fd("\nstopped by signal SIGINT", STDOUT_FILENO);
}