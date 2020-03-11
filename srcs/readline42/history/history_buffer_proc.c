/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_buffer_proc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 19:07:04 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/11 14:17:25 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

/*
** Buf scroll is used only with the stated buf len. If buf len changes
** buf should be corrected by the make_hist_buffer_smaller function
*/

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
	g_hist.last_fc = g_hist.last;
	g_hist.counter = g_hist.last + 1;
	return (0);
}

/*
** We save the buffer if it exists - as big buffer as we have from the file
** If HISTSIZE  - the default buffer size is less than we saved - we prepare
** a new buffer (a smaller one)
*/

int				save_hist_buffer(int fd)
{
	size_t		i;

	i = read_hist_from_file(fd);
	g_hist.last = i - 1;
	g_hist.counter = i;
	g_hist.start = i;
	g_hist.last_fc = g_hist.last;
	if (g_hist.counter > MAX_HISTBUF)
		g_hist.hist = make_hist_buffer_smaller(MAX_HISTBUF);
	return (0);
}

char			**make_hist_buffer_smaller(int size)
{
	char		**history;
	size_t		i;
	size_t		j;

	i = g_hist.counter - size;
	j = 0;
	history = (char**)ft_xmalloc(sizeof(char*) * (size + 1));
	while (g_hist.hist[i] && i < g_hist.counter)
	{
		history[j] = ft_strdup(g_hist.hist[i]);
		i++;
		j++;
	}
	g_hist.len = size;
	g_hist.start = 0;
	g_hist.last = g_hist.len - 1;
	g_hist.counter = g_hist.len;
	if (g_hist.last_fc > g_hist.len)
		g_hist.last_fc = g_hist.last;
	ft_arrdel(g_hist.hist);
	return (history);
}

int				check_if_histsize_changed(void)
{
	size_t		i;
	size_t		j;
	int			user_len;

	i = find_in_variables(g_shvar, &j, "HISTSIZE=");
	if (!ft_isdigit(g_shvar[i][j]))
		return (0);
	user_len = ft_atoi(g_shvar[i] + j);
	if (user_len < 0 || user_len > HISTORY_LIMIT)
		return (0);
	else if (user_len > 0 && user_len > g_hist.len)
	{
		g_hist.hist = ft_realloc_array(&g_hist.hist,
			g_hist.len, user_len);
		g_hist.len = user_len;
	}
	else if (user_len >= 0 && user_len < g_hist.len)
		g_hist.hist = make_hist_buffer_smaller(user_len); //TODO проверить
	return (0);
}
