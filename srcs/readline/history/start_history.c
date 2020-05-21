#include "shell42.h"
#include "readline.h"

int				start_history(void)
{
	int			fd;
	size_t		j;
	size_t		i;

	init_history_buffer();
	// i = find_in_variables(g_env, &j, "HOME=");
	// tmp = (i < 0) ? define_history_file() :
	// 	ft_strjoin(&g_envi[i][j], "/.42sh_history");
	i = find_in_variables(g_shvar, &j, "HISTFILE=");
	fd = open(g_shvar[i] + j, O_RDONLY);
	if (fd < 0)
		return (0);
	save_hist_buffer(fd);
	close(fd);
	return (0);
}

void			init_history_buffer(void)
{
	size_t		i;
	int			tmp;

	i = 0;
	while (ft_strncmp(g_shvar[i], "HISTSIZE=",
		(tmp = ft_strchri(g_shvar[i], '=') + 1)) != 0)
		i++;
	g_hist.len = ft_atoi(&g_shvar[i][tmp]) + 1;
	g_hist.hist = (char**)ft_xmalloc(sizeof(char*) * (g_hist.len + 1));
	g_hist.last = -1;
	g_hist.start = 0;
	g_hist.counter = 0;
	g_hist.last_fc = 0;
}

/*
** We find the directory we are in a try to find a history file. If we find -
** send it back to the start_history function and save everything from file to
** the buffer. If we can not open it - the buffer will start with the first
** command in the session
*/

char			*define_history_file(void)
{
	size_t		li;
	size_t		sy;

	li = find_in_variables(g_rdovar, &sy, "42SH=");
	return (ft_strjoin(&g_rdovar[li][sy], "/.42sh_history"));
}

/*
** Numeration in the file starts with 1 but in the history buffer - from 0.
** We should make one line - the last in the buffer empty, because after
** the buffer is scrolled, a new cmd will lie there
** In the end of each command there is '\n' lying - if there was ctrl-d
** exit from readline when the prompt was not main-prompt - there is a EOF
** symbol in the line only
*/

int				add_to_history(char *cmd)
{
	int			flag;

	flag = 0;
	if (g_hist.last + 1 >= g_hist.len - 1 &&
		g_prompt.prompt_func == main_prompt && g_hist.len > 0)
		scroll_hist_buffer(1);
	if (g_prompt.prompt_func == main_prompt && g_hist.len > 0)
	{
		g_hist.last++;
		g_hist.hist[g_hist.last] = ft_strdup(cmd);
		g_hist.last_fc++;
		if (g_hist.last_fc > HISTORY_LIMIT)
			g_hist.last_fc = 1;
	}
	else if (g_prompt.prompt_func != main_prompt &&
		g_prompt.prompt_func != heredoc_prompt && g_hist.len > 0)
	{
		flag = (cmd[0] == EOF) ? EOF : 0;
		add_other_prompts_history(cmd, flag);
	}
	g_hist.counter = g_hist.last + 1;
	return (0);
}

int				add_other_prompts_history(char *cmd, int flag)
{
	if (g_hist.hist[g_hist.last][0] != 0 && flag == 0)
		g_hist.hist[g_hist.last] =
			ft_strrejoin(g_hist.hist[g_hist.last], cmd);
	clean_parser42();
	g_cmd = ft_strdup(g_hist.hist[g_hist.last]);
	g_cmd = (flag == EOF) ? ft_straddsy(g_cmd, EOF) : g_cmd;
	g_cmd_size = ft_strlen(g_cmd);
	ft_get_techline(g_cmd, &g_techline);
	return (0);
}
