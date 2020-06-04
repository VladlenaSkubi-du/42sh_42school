#include "shell42.h"
#include "readline.h"

/*
** Buf scroll is used only with the stated buf len. If buf len changes
** buf should be corrected by the make_hist_buffer_smaller function
*/

int					scroll_hist_buffer(int num)
{
	int				i;

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
	int			i;

	i = read_hist_from_file(fd);
	g_hist.last = i - 1;
	g_hist.counter = i;
	g_hist.start = i;
	g_hist.last_fc = (g_hist.last > 0) ? g_hist.last + 1 : 1;
	if (g_hist.len > MAX_HISTBUF)
		g_hist.hist = make_hist_buffer_smaller((MAX_HISTBUF > HISTORY_LIMIT) ?
		HISTORY_LIMIT : MAX_HISTBUF);
	if (g_hist.last_fc > HISTORY_LIMIT)
		g_hist.last_fc = HISTORY_LIMIT;
	return (0);
}

char			**make_hist_buffer_smaller(int size)
{
	char		**history;
	int			i;
	int			j;

	if (size > HISTORY_LIMIT)
		size = 500;
	i = (g_hist.counter >= size) ? g_hist.counter - size : 0;
	j = 0;
	history = (char**)ft_xmalloc(sizeof(char*) * (size + 2));
	while (g_hist.hist[i] && j < size + 1)
	{
		history[j] = ft_strdup(g_hist.hist[i]);
		i++;
		j++;
	}
	free(g_hist.hist[g_hist.len]);
	g_hist.len = size + 1;
	g_hist.start = 0;
	g_hist.last = (i > g_hist.len) ? g_hist.len - 1 : i - 1;
	g_hist.counter = g_hist.last + 1;
	ft_arrdel(g_hist.hist);
	return (history);
}

int				check_if_histsize_changed(void)
{
	// size_t		li;
	// size_t		co;
	int			li;
	int			co;
	int			user_len;

	li = find_in_variable(&co, "HISTSIZE");
	if (!ft_isdigit(g_envi[li][co]))
		return (0);
	user_len = ft_atoi(g_envi[li] + co);

	// li = find_in_variables(g_shvar, &co, "HISTSIZE=");
	// if (!ft_isdigit(g_shvar[li][co]))
	// 	return (0);
	// user_len = ft_atoi(g_shvar[li] + co);
	if (user_len < 0 || user_len > HISTORY_LIMIT)
		return (0);
	else if (user_len > 0 && user_len > g_hist.len)
	{
		g_hist.hist = ft_realloc_array(&g_hist.hist,
			g_hist.len, user_len + 2);
		g_hist.len = user_len + 1;
	}
	else if (user_len > 0 && user_len < g_hist.len)
		g_hist.hist = make_hist_buffer_smaller(user_len); //TODO проверить
	else if (user_len == 0)
	{
		free(g_hist.hist[g_hist.len + 1]);
		ft_arrdel(g_hist.hist);
		init_history_buffer(0 + 1);
	}
	return (0);
}

int		delete_last_history_element(void)
{
	free(g_hist.hist[g_hist.last]);
	g_hist.hist[g_hist.last] = NULL;
	g_hist.counter--;
	g_hist.last--;
	if (g_hist.last_fc < 1)
	   g_hist.last_fc =  g_hist.len - 1;
	return (0);
}