/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 17:35:22 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/04 17:15:35 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int				start_history(void)
{
	int			fd;
	char		*file;
	char		*tmp;
	int			co;
	int			li;

	li = find_in_variable(&co, "HISTSIZE");
	init_history_buffer(ft_atoi(g_envi[li] + co) + 1);
	li = find_in_variable(&co, "HISTFILE");
	file = define_history_file();
	tmp = ft_strjoin("HISTFILE=", file);
	change_env_value(tmp, li);
	free(tmp);
	free(file);
	fd = open(g_envi[li] + co, O_RDONLY);
	if (fd < 0)
		return (0);
	save_hist_buffer(fd);
	close(fd);
	return (0);
}

/*
** The buffer size for history len is num + 1 for the current line
** to save and + 1 for the end of the array
*/

void			init_history_buffer(int size)
{
	g_hist.len = size;
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
	int			li;
	int			co;
	char		*file;

	li = find_in_variable(&co, "HOME");
	if (li < 0)
		li = find_in_variable(&co, "42SH");
	file = ft_strjoin(g_envi[li] + co, "/.42sh_history");
	return (file);
}

/*
** Numeration in the file starts with 1 but in the history buffer - from 0.
** We should make one line - the last in the buffer empty, because after
** the buffer is scrolled, a new cmd will lie there
** In the end of each command there is '\n' lying - if there was ctrl-d
** exit from readline when the prompt was not main-prompt - there is a EOF
** symbol in the line only
** New line to history is added only from the main-prompt
*/

int				add_to_history(char *cmd)
{
	int			flag;

	flag = 0;
	if (g_hist.last + 1 >= g_hist.len - 1 &&
			g_prompt.prompt_func == main_prompt && g_hist.len > 1)
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

/*
** Here we add the last cmd coming to parser to the history-buffer
** because if we have prompts dquote, backslash and so on, all the
** "cmd-parts" are saved in the history. Only heredoc "parts" are not
** saved in the history because they are considered as a document.
** After history buffer, we change the g_cmd and other parser globals
** that start to include the whole command - with its beginning from
** the history.
*/

int				add_other_prompts_history(char *cmd, int flag)
{
	if (g_hist.hist[g_hist.last][0] != 0 && flag == 0)
		g_hist.hist[g_hist.last] =
			ft_strrejoin(g_hist.hist[g_hist.last], cmd);
	clean_parser42();
	if (flag == EOF)
	{
		g_cmd = (char*)ft_xmalloc(ft_strlen(g_hist.hist[g_hist.last]) + 2);
		ft_strcpy(g_cmd, g_hist.hist[g_hist.last]);
		g_cmd = ft_straddsy(g_cmd, EOF);
	}
	else
		g_cmd = ft_strdup(g_hist.hist[g_hist.last]);
	// g_cmd_size = ft_strlen(g_cmd);
	ft_get_techline(g_cmd, &g_techline);
	return (0);
}
