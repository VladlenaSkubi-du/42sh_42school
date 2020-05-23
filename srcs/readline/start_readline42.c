#include "shell42.h"
#include "shell42.h"

void			init_readline(void)
{
	g_rline.cmd = (char *)ft_xmalloc(CMD_SIZE + 1);
	g_rline.cmd_len = 0;
	g_rline.pos = 0;
	g_rline.pos_x = 0;
	g_rline.pos_y = 0;
	g_rline.str_num = 1;
	g_rline.cmd_buff_len = CMD_SIZE + 1;
	g_rline.flag = 0;
}

void			bzero_readline(void)
{
	if (ioctl(1, TIOCGWINSZ, &g_screen))
	{
		error_handler(TERMINAL_EXISTS, NULL);
		clean_everything();
		exit(TERMINAL_EXISTS);
	}
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

/*
** If we did not get describtion of the terminal
** or there is no termcap library, we are still able
** to make the line alterable with readline-simple
** And from here we go to parser in the interactive mode
*/

int				start_readline42(int tmp)
{
	char		*final;

	bzero_readline();
	(tmp != 1) ? readline_simple() : readline();
	check_menu();
	reset_canonical_input();
	signals_reroute(2);
	final = finalize_cmd(g_rline.cmd);
	clean_readline42();
	parser(final);
	return (0);
}

char			*finalize_cmd(char *cmd)
{
	char		*out;
	char		*tmp;

	tmp = ft_strtrim(cmd);
	if (ft_strlen(tmp) == 0)
	{
		out = ft_xmalloc(1);
		free(tmp);
		return (out);
	}
	if (g_rline.cmd_len == 0)
		out = ft_strdup(cmd);
	else
		out = ft_strjoin(cmd, "\n");
	free(tmp);
	return (out);
}
