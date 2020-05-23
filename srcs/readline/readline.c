#include "shell42.h"
#include "readline.h"

char	*readline(void)
{
	char	temp[10];

	while (read(STDIN_FILENO, temp, 1) > 0 && *temp != '\n')
	{
		if (readline_choice(*temp) == OUT)
			break ;
	}
	if (g_rline.cmd_len > 0)
	{
		check_menu();
		position_cursor_for_menu(g_rline.cmd_len);
		putcap("cd");
	}
	else
		ft_putendl_fd(0, STDOUT_FILENO);
	action_alloc_management(NULL, 1);
	return (g_rline.cmd);
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
		check_menu();
		escape_init();
	}
	else if (ft_isprint(sy))
	{
		check_menu();
		if (char_add(sy, NULL) == OUT)
			return (OUT);
		kirill_lgbt(sy);
	}
	return (0);
}

int		route_exit(void)
{
	t_ltree	*pos;
	
	check_menu();
	if (g_prompt.prompt_func == main_prompt)
	{
		pos = (t_ltree*)ft_xmalloc(sizeof(t_ltree));
		ltree_init(pos);
		pos->ar_v = (char**)ft_xmalloc(3 * sizeof(char*));
		pos->ar_v[0] = ft_strdup("exit");
		pos->ar_v[1] = ft_strdup("0");
		action_alloc_management(NULL, 1);
		reset_canonical_input();
		clean_readline42();
		btin_exit(pos);
	}
	if (g_prompt.prompt_func != main_prompt)
	{
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