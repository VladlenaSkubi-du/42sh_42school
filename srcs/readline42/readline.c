#include "shell42.h"
#include "readline.h"

/*
** Readline_choice is a router to analyse what was pushed by the user
** @sy is symbol
*/

int		readline_choice(char sy)
{
	if (ctrl_key(sy) == OUT)
		return (OUT);
	if (sy == '\033')
	{
		check_menu();
		escape_init();
	}
	else if (ft_isprint(sy))
	{
		check_menu();
		char_add(sy, NULL);
		kirill_lgbt(sy);
	}
	return (0);
}

char	*readline(void)
{
	char			temp;

	init_termcap();
	while (read(1, &temp, 1) > 0 && temp != '\n')
	{
		if (readline_choice(temp) == OUT)
			break ;
	}
	if (g_rline.cmd_len > 0)
	{
		check_menu();
		position_cursor_for_menu(g_rline.cmd_len);
		putcap("cd");
	}
	else
		ft_putendl_fd(0, STDIN_FILENO);
	action_alloc_management(NULL, 1);
	save_current_grline(2);
	return (g_rline.cmd);
}

void	init_readline(void)
{
	if (ioctl(1, TIOCGWINSZ, &g_screen))
	{
		ft_putendl_fd("Can't get terminal dimensions", 2);
		clean_everything();
		exit(TERMINAL_EXISTS);
	}
	g_rline.prompt_len = prompt_len();
	g_rline.cmd = (char *)ft_xmalloc(CMD_SIZE + 1);
	g_rline.cmd_len = 0;
	g_rline.pos = 0;
	g_rline.pos_x = g_rline.prompt_len;
	if (g_rline.prompt_len >= g_screen.ws_col)
		g_rline.pos_x = g_rline.prompt_len % g_screen.ws_col;
	g_rline.pos_y = 0;
	g_rline.str_num = 1;
	g_rline.cmd_buff_len = CMD_SIZE + 1;
	g_rline.flag = 0;
}

int					route_exit(void)
{
	if (g_prompt.prompt_func == main_prompt)
	{
		check_menu();
		action_alloc_management(NULL, 1);
		reset_canonical_input();
		clean_readline42();
		btin_exit(SUCCESS);
	}
	if (g_prompt.prompt_func != main_prompt)
	{
		check_menu();
		g_rline.cmd = ft_straddsy(g_rline.cmd, EOF);
		return (OUT);
	}
	return (0);
}
