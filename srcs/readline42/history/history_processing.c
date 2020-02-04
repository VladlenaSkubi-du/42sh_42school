/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_processing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:18:29 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/04 19:17:56 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int                 add_to_history(char *cmd)
{
	if (g_hist.last >= g_hist.len)
		scroll_hist_buffer(1);
	g_hist.hist[g_hist.last] = ft_strdup(cmd);
	if (g_prompt.prompt_func == main_prompt)
		g_hist.last++;
	else
	{
		if (g_hist.hist[g_hist.last][0] != 0)
			g_hist.hist[g_hist.last] =
				ft_strrejoin(g_hist.hist[g_hist.last], cmd);
	}
	// в блоке возврата в ридлайн при закрытии ридлайна (любым способом увеличивается счетчик команд и промпт переводится на main)
	// вместо буфера в счетчике команд можно использовать буфер истории - значение перезаписывается
	// при экранировании перезапись с убиранием слешей идет СРАЗУ
	//printf("last %s\nfirst %s\nlast = %zu, len = %zu\n", g_hist.hist[g_hist.last - 1], g_hist.hist[g_hist.start], g_hist.last, g_hist.len);
	return (0);
}

int                 scroll_hist_buffer(size_t num)
{
	size_t          i;

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
	return (0);
}

int					fill_in_file(void)
{
	size_t			i;
	size_t			j;
	int				fd;
	int				user_len;
	
	i = find_in_variables(g_shvar, &j, "HISTFILE=");
	fd = open(g_shvar[i] + j, O_APPEND);
	if (fd == -1)
		fd = creat(g_shvar[i] + j, S_IRUSR|S_IWUSR);
	i = find_in_variables(g_shvar, &j, "HISTFILESIZE=");
	user_len = ft_atoi(g_shvar[i] + j);
	if (user_len <= g_hist.len)
		g_hist.start = g_hist.last - g_hist.len;
	i = g_hist.start;
	while (g_hist.hist[i] && i < g_hist.len - 1)
	{
		write(fd, g_hist.hist[i], ft_strlen(g_hist.hist[i]));
		write(fd, "\n", 1);
		i++;
	}
	if (g_hist.hist[i])
		write(fd, g_hist.hist[i], ft_strlen(g_hist.hist[i]));
	return (0);
}