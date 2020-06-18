#include "shell42.h"
#include "builtin42.h"

/*
** The list of the whole history buffer
** If HISTORY_LIMIT or 32767 is reached, numeration continues with 1
*/

int					btin_history(t_ltree *pos)
{
	int				flags;
	int				i;
	int				j;
	int				tmp;
	
	flags = find_options(2, (char*[]){"c", "--help"}, pos->ar_v);
	if (pos->ar_c == 1 && !flags)
		return (btin_history_noargs());
	if (flags == 0x10000)
		return (usage_btin("history"));
	i = 0;
	while (pos->ar_v[++i] && pos->ar_v[i][0] == '-')
	{
		j = 0;
		if (!pos->ar_v[i][1])
			return (invalid_option_btin(pos->ar_v[i], pos->ar_v[0]));
		while (pos->ar_v[i][++j] == 'c' && pos->ar_v[i][j])
			tmp = i;
		if (pos->ar_v[i][j] == '-' && !pos->ar_v[i][j + 1])
			break ;
		if (j > 1 && (!(pos->ar_v[i][j] == 'c' || pos->ar_v[i][j] == '\0')))
			return (invalid_option_btin(&pos->ar_v[i][j], pos->ar_v[0]));	
	}
	return ((tmp > 0) ? btin_history_clear() : btin_history_noargs());
}

int					btin_history_noargs(void)
{
	int				i;
	int				num;
	int				tmp;

	i = 0;
	num = g_hist.last_fc - ((g_hist.last + 1 == g_hist.len) ?
		g_hist.len - 1 : g_hist.last) + 1;
	num += (num < 1) ? HISTORY_LIMIT : 0;
	while (g_hist.hist[i] && i < g_hist.len)
	{
		if (num > HISTORY_LIMIT)
			num = 1;
		tmp = ft_strlen(g_hist.hist[i]);
		if (tmp > 0 && g_hist.hist[i][tmp - 1] == '\n')
			tmp -= 1;
		ft_printf("%5d  %.*s\n", num, tmp, g_hist.hist[i]);
		num++;
		i++;
	}
	return (0);
}

int					btin_history_clear(void)
{
	int				li;
	int				co;
	int				size;

	ft_arrdel(g_hist.hist);
	g_hist.hist = NULL;
	li = find_in_variable(&co, "HISTSIZE");
	if (!((g_envi[li][0] && (g_envi[li][0] & SET_VIS)) ||
			ft_isdigit(g_envi[li][co])))
		size = MAX_HISTBUF;
	size = ft_atoi(g_envi[li] + co);
	if (size < 0 || size > HISTORY_LIMIT)
		size = MAX_HISTBUF;
	init_history_buffer(size);
	return (0);
}
