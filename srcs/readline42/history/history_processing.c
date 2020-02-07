/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_processing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:18:29 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/07 14:40:55 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int					add_to_history(char *cmd)
{
	int				flag;
	
	// if (g_hist.last >= g_hist.len)
	// 	scroll_hist_buffer(1); //слетает после скролла
	flag = 0;
	if (g_prompt.prompt_func == main_prompt)
	{
		g_hist.last++;
		g_hist.hist[g_hist.last] = ft_strdup(cmd);
	}
	else
	{
		if (cmd[0] == EOF)
			flag = EOF;
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
	// в блоке возврата в ридлайн при закрытии ридлайна (любым способом увеличивается счетчик команд и промпт переводится на main)
	// вместо буфера в счетчике команд можно использовать буфер истории - значение перезаписывается
	// при экранировании перезапись с убиранием слешей идет СРАЗУ
	//printf("last %s\nfirst %s\nlast = %zu, len = %zu\n", g_hist.hist[g_hist.last - 1], g_hist.hist[g_hist.start], g_hist.last, g_hist.len);
	return (0);
}

int					scroll_hist_buffer(size_t num)
{
	size_t			i;

	i = 0;
	while (i < num)
	{
		free(g_hist.hist[i]);
		i++;
	}
	i = 0;
	while (g_hist.hist[i + num] && i + num < g_hist.len)
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
	printf("user_len = %d\n", user_len);
	fd = open_hist_file(user_len, path);
	free(path);
	if (fd < 0)
		return (1);
	i = g_hist.start;
	while (g_hist.hist[i] && i < g_hist.len)
	{
		write(fd, g_hist.hist[i], ft_strlen(g_hist.hist[i]));
		// write(fd, "\n", 1);
		i++;
	}
	close(fd);
	return (0);
}

int					open_hist_file(int user_len, char *path)
{
	int				fd;

	if (user_len != g_hist.len || g_hist.start != g_hist.start_control)
	{
		fd = open(path, O_WRONLY | O_TRUNC | O_CREAT | O_SYNC,
			S_IRUSR | S_IWUSR);
		g_hist.start = 0;
	}
	else
		fd = open(path, O_WRONLY | O_APPEND | O_CREAT | O_SYNC,
			S_IRUSR | S_IWUSR);
	return (fd);
}
