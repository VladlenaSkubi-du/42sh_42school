/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_processing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:18:29 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/07 22:16:31 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

/*
** Numeration in the file starts with 1 but in the history buffer - from 0.
** We should make one line - the last in the buffer empty, because after
** the buffer is scrolled, a new cmd will lie there
*/

int					add_to_history(char *cmd)
{
	int				flag;

	flag = 0;
	if (g_hist.last + 1 > g_hist.len - 1)
		scroll_hist_buffer(1);
	if (g_prompt.prompt_func == main_prompt)
	{
		g_hist.last++;
		g_hist.hist[g_hist.last] = ft_strdup(cmd);
	}
	else
	{
		flag = (cmd[0] == EOF) ? EOF : 0;
		if (g_hist.hist[g_hist.last][0] != 0 && flag == 0)
			g_hist.hist[g_hist.last] =
				ft_strrejoin(g_hist.hist[g_hist.last], cmd);
		clean_parser42();
		g_cmd = ft_strdup(g_hist.hist[g_hist.last]);
		if (flag == EOF)
			g_cmd = ft_straddsy(g_cmd, EOF);
		g_cmd_size = ft_strlen(g_cmd);
		ft_get_techline();
	}
	return (0);
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
		g_hist.hist[i] =  g_hist.hist[i + num];
		i++;
	}
	g_hist.last -= num;
	g_hist.start = 0;
	return (0);
}

static int	print_all_vars(void)
{
	size_t	i;

	i = 0;
	printf("%.10s\n", "\n\nENVIRON");
	while (g_env[i])
		printf("%s\n", g_env[i++]);
	i = 0;
	printf("%.10s\n", "\n\nWORKING");
	while (g_shvar[i])
		printf("%s\n", g_shvar[i++]);
	i = 0;
	printf("%.10s\n", "\n\nLOCAL");
	while (g_lovar[i])
		printf("%s\n", g_lovar[i++]);
	return (0);
}

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
	user_len = ft_atoi(g_shvar[i] + j);
	printf("user_len = %d - %d\n", user_len, g_hist.len);
	fd = open_hist_file(user_len, path);
	free(path);
	if (fd < 0)
		return (1);
	i = g_hist.start;
	while (g_hist.hist[i] && i < g_hist.len)
	{
		write(fd, g_hist.hist[i], ft_strlen(g_hist.hist[i]));
		i++;
	}
	close(fd);
	return (0);
}

int					open_hist_file(int user_len, char *path)
{
	int				fd;

	if (g_hist.start != g_hist.start_control ||
		user_len < g_hist.len || user_len == 0)
	{
		fd = open(path, O_WRONLY | O_TRUNC | O_CREAT | O_SYNC,
			S_IRUSR | S_IWUSR);
		g_hist.start = (user_len == 0) ? 0 : g_hist.last - user_len + 1;
	}
	else
		fd = open(path, O_WRONLY | O_APPEND | O_CREAT | O_SYNC,
			S_IRUSR | S_IWUSR);
	return (fd);
}

int					check_if_histsize_changed(void)
{
	size_t			i;
	size_t			j;
	int				user_len;
	char			**new;

	i = find_in_variables(g_shvar, &j, "HISTFILESIZE=");
	if (!ft_isdigit(g_shvar[i][j]))
		return (0);
	user_len = ft_atoi(g_shvar[i] + j);
	if (user_len > 0 && user_len > g_hist.len)
	{		
		new = (char**)ft_xmalloc(sizeof(char*) * (user_len + 1));
		new[user_len] = 0;
		i = 0;
		while (i < g_hist.len)
		{
			new[i] = ft_strdup(g_hist.hist[i]);
			i++;
		}
		ft_arrdel(g_hist.hist);
		g_hist.hist = new;
		g_hist.len = user_len;
		g_hist.start = 0;
	}
	return (0);
}
