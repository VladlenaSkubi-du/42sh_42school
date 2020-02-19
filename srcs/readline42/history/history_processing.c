/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_processing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:18:29 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/19 12:20:12 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

/*
** Numeration in the file starts with 1 but in the history buffer - from 0.
** We should make one line - the last in the buffer empty, because after
** the buffer is scrolled, a new cmd will lie there
** In the end of each command there is '\n' lying - if there was ctrl-d
** exit from readline when the prompt was not main-prompt - there is a EOF
** symbol in the line only
*/

int					add_to_history(char *cmd) //Когда будет запуск, сделать перезапись истории по командам, осторожнее с fc
{
	int				flag;

	flag = 0;
	if (g_hist.last + 1 > g_hist.len - 1 &&
		g_prompt.prompt_func == main_prompt)
		scroll_hist_buffer(1);
	if (g_prompt.prompt_func == main_prompt)
	{
		g_hist.last++;
		g_hist.hist[g_hist.last] = ft_strdup(cmd);
	}
	else if (g_prompt.prompt_func != main_prompt &&
		g_prompt.prompt_func != heredoc_prompt)
	{
		flag = (cmd[0] == EOF) ? EOF : 0;
		if (g_hist.hist[g_hist.last][0] != 0 && flag == 0)
			g_hist.hist[g_hist.last] =
				ft_strrejoin(g_hist.hist[g_hist.last], cmd);
		clean_parser42();
		g_cmd = ft_strdup(g_hist.hist[g_hist.last]);
		g_cmd = (flag == EOF) ? ft_straddsy(g_cmd, EOF) : g_cmd;
		g_cmd_size = ft_strlen(g_cmd);
		ft_get_techline();
	}
	return (0);
}

/*
** We chechk one more time the HISTORY path - if user wants to change
** the default path for the file and the HISTORYSIZE variable
** If it is invalid, the default configurations won't change.
*/

int					fill_hist_in_file(void)
{
	size_t			i;
	size_t			j;
	int				fd;
	char			*path;
	int				user_len;

	j = 0;
	i = find_in_variables(g_shvar, &j, "HISTFILE=");
	path = ft_strdup(g_shvar[i] + j);
	i = find_in_variables(g_shvar, &j, "HISTFILESIZE=");
	if (!ft_isdigit(g_shvar[i][j]))
		user_len = MAX_HISTORY;
	else
	{
		user_len = ft_atoi(g_shvar[i] + j);
		if (user_len < 0 || user_len > 32767)
			user_len = MAX_HISTORY;
	}
	fd = open_hist_file(user_len, path);
	free(path);
	if (fd < 0)
		return (0);
	insert_hist_in_file(fd);
	close(fd);
	return (0);
}

int					insert_hist_in_file(int fd)
{
	int				i;
	int				tmp;

	i = g_hist.start;
	while (g_hist.hist[i] && i < g_hist.len)
	{
		tmp = ft_strlen(g_hist.hist[i]);
		if (tmp > 0 && g_hist.hist[i][tmp - 1] == '\n')
			tmp -= 1;
		write(fd, g_hist.hist[i], tmp);
		write(fd, "\n", 1);
		// printf("%d - %.*s\n", i + 1, tmp, g_hist.hist[i]);
		i++;
	}
	return (0);
}

int					open_hist_file(int user_len, char *path)
{
	int				fd;
	char			*default_path;

	default_path = define_history_file();
	// printf("user_len = %d - %d\n", user_len, g_hist.len);
	if (g_hist.start != g_hist.start_control ||
		user_len < g_hist.len || user_len == 0)
	{
		fd = open(path, O_WRONLY | O_TRUNC | O_CREAT | O_SYNC,
			S_IRUSR | S_IWUSR);
		if (user_len < g_hist.len && user_len > 0)
			g_hist.start = g_hist.last - user_len + 1;
		else if (user_len == 0)
			g_hist.len = 0;
	}
	else
		fd = open(path, O_WRONLY | O_APPEND | O_CREAT | O_SYNC,
			S_IRUSR | S_IWUSR);
	if (ft_strcmp(path, default_path) != 0 && fd < 0)
		open_hist_file(user_len, default_path);
	free(default_path);
	return (fd);
}

int					scroll_hist_buffer(size_t num)
{
	size_t			i;

	i = 0;
	while (i < num)
	{
		free(g_hist.hist[i]);
		g_hist.hist[i] = NULL;
		i++;
	}
	i = 0;
	while (i < g_hist.len - num)
	{
		g_hist.hist[i] = g_hist.hist[i + num];
		i++;
	}
	g_hist.last -= num;
	g_hist.start = 0;
	return (0);
}
