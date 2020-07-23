#include "shell42.h"
#include "readline.h"

int		readline(void)
{
	char	temp[10];

	init_termcap();
	while (read(STDIN_FILENO, temp, 1) > 0 && *temp != '\n')
	{
		if (readline_choice(*temp) == OUT)
			break ;
	}
	if (g_rline.cmd_len > 0)
	{
		check_after_line();
		position_cursor_after_line(g_rline.cmd_len);
		putcap("cd");
	}
	else
		ft_putendl_fd(0, STDOUT_FILENO);
	action_alloc_management(NULL, 1);
	clean_termcap();
	return (0);
}

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
		check_after_line();
		escape_init();
	}
	else if (ft_isprint(sy))
	{
		check_after_line();
		if (char_add(sy, NULL) == OUT)
			return (OUT);
		kirill_lgbt();
	}
	return (0);
}

/*
** You can come to route_exit when you push ctrl-D
** Depending on the prompt you are in (main, dquote and so on),
** you will exit the program or get a syntax error
*/

int		route_exit(void)
{
	t_ltree		*pos;
	
	check_after_line();
	if (g_prompt.prompt_func == main_prompt)
	{
		pos = (t_ltree*)ft_xmalloc(sizeof(t_ltree));
		ltree_init(pos);
		pos->ar_v = (char**)ft_xmalloc(3 * sizeof(char*));
		pos->ar_v[0] = ft_strdup("exit");
		pos->ar_v[1] = ft_strdup("0");
		action_alloc_management(NULL, 1);
		reset_canonical_input();
		free(g_rline.cmd);
		btin_exit(pos);
	}
	else
	{
		if (g_rline.cmd_len >= g_rline.cmd_buff_len - 1)
			realloc_readline_cmd();
		g_rline.cmd = ft_straddsy(g_rline.cmd, EOF);
		return (OUT);
	}
	return (0);
}

/*
** Should beep and do nothing - bell
** Does so if there is a wrong action
*/

int		incorrect_sequence(void)
{
	putcap("bl");
	return (1);
}

/*
** After any key except of TAB is pushed, the menu under
** the line is cleared
** The same happends with the comments under the line
*/

int		check_after_line(void)
{
	if (g_rline.flag & TAB)
	{
		clean_after_line();
		g_rline.flag &= ~TAB;
		clear_completion(0);
	}
	else if ((g_rline.flag & AFTER_LINE) ||
			(g_rline.flag & AFTER_LINE_HIST))
	{
		clean_after_line();
		g_rline.flag &= ~AFTER_LINE;
		g_rline.flag &= ~AFTER_LINE_HIST;
	}
	return (0);
}
