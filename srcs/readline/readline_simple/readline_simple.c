#include "shell42.h"
#include "readline.h"

int					bell_sound(void)
{
	write(STDOUT_FILENO, "\a", 1);
	return (1);
}

int					sreadline_choice(char sy)
{
	if (sy == '\033')
		sescape_init();
	else if (ft_isprint(sy))
	{
		if (schar_add(sy) == OUT)
			return (OUT);
	}
	else if (sy == 127 || sy == '\010')
		sbackspace_proc();
	else if (sy == '\002')
		sesc_left();
	else if (sy == '\006')
		sesc_right();
	else if (sy == '\001')
		make_sctrl_a();
	else if (sy == '\005')
		make_sctrl_e();
	else if (sy == '\004')
		make_exit();
	return (0);
}

char				*readline_simple(void)
{
	char			c;

	while (read(STDIN_FILENO, &c, 1) && c != '\n')
	{
		if (sreadline_choice(c) == OUT)
			break ;
	}
	ft_putendl_fd(0, STDOUT_FILENO);
	return (g_rline.cmd);
}

int					make_exit(void)
{
	t_ltree			*pos;
	
	if (g_rline.pos == 0 && g_rline.cmd_len == 0 &&
		g_prompt.prompt_func == main_prompt)
	{
		pos = (t_ltree*)ft_xmalloc(sizeof(t_ltree));
		ltree_init(pos);
		pos->ar_v = (char**)ft_xmalloc(3 * sizeof(char*));
		pos->ar_v[0] = ft_strdup("exit");
		pos->ar_v[1] = ft_strdup("0");
		reset_canonical_input();
		clean_readline42();
		btin_exit(pos);
	}
	else if (g_rline.pos == 0 && g_rline.cmd_len == 0 &&
		g_prompt.prompt_func != main_prompt)
	{
		g_rline.cmd = ft_straddsy(g_rline.cmd, EOF);
		return (OUT);
	}
	return (0);
}