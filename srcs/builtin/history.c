#include "shell42.h"
#include "builtin42.h"

/*
** The list of the whole history buffer
** If HISTORY_LIMIT or 32767 is reached, numeration continues with 1
*/

int					btin_history(void)
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

/*
** Builtin !: !! is the last history-cmd in the buffer
** !word is the last history-cmd that starts with word
** !number is the history-cmd according to the number
** !-number is the history-cmd of the same number if count from
** the last cmd
*/

int					btin_exsign(t_ltree *pos)
{
	int				i;
	int				len;
	int				num;
	int				count;
	int				temp;

	if (g_hist.len < 1 || g_hist.last < 0)
		return (btin_exsign_print_message(pos->ar_v[0]));
	if (pos->ar_v[0][0] == '!' && pos->ar_v[0][1] == '\0')
		return (0);
	i = 1;
	len = ft_strlen(pos->ar_v[0]);
	if (pos->ar_v[0][1] == '-' || ft_isdigit(pos->ar_v[0][1]))
	{
		(pos->ar_v[0][1] == '-') ? i++ : 0;
		while (pos->ar_v[0][i] && ft_isdigit(pos->ar_v[0][i]))
			i++;
		if (i == len)
		{
			num = ft_atoi(pos->ar_v[0] + 1);
			if (pos->ar_v[0][1] == '-')
			{
				count = btin_fc_negative_int__exec(num);
				if (count == 0 && num != 0)
					btin_exsign_print_message(pos->ar_v[0]);
			}
			else
			{
				temp = g_hist.last_fc - ((g_hist.last + 1 == g_hist.len) ?
					g_hist.len - 1 : g_hist.last) + 1;
				count = btin_fc_positive_int__exec(num, temp, g_hist.last_fc);
			}
		}
	}

	return (0);
}

int					btin_exsign_print_message(char *arg)
{
	// ft_putstr_fd(find_env_value("0"), STDOUT_FILENO);
	ft_putstr_fd(": ", STDOUT_FILENO);
	ft_putstr_fd(arg, STDOUT_FILENO);
	ft_putendl_fd(": event not found", STDOUT_FILENO);
	return (0);
}

int					btin_exsign_num_search(int num)
{
	return (0);
}