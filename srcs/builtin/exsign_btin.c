#include "shell42.h"
#include "builtin42.h"

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

	if (g_hist.len < 1 || g_hist.last < 0)
		return (btin_exsign_print_message(pos->ar_v[0]));
	if (pos->ar_v[0][0] == '!' && pos->ar_v[0][1] == '\0')
		return (0);
	if (pos->ar_v[0][0] == '!' && pos->ar_v[0][1] == '!' &&
			pos->ar_v[0][2] == '\0')
		return (btin_exsign_make_substitution(pos, g_hist.hist[g_hist.last]));
	i = (pos->ar_v[0][1] == '-') ? 1 : 0;
	while (pos->ar_v[0][++i])
		if (!(pos->ar_v[1][i] >= '0' && pos->ar_v[1][i] <= '9'))
		{
			if ((i = find_in_history(&pos->ar_v[0][1])) == -1)
				return (btin_exsign_print_message(pos->ar_v[0]));
			return (btin_exsign_make_substitution(pos, g_hist.hist[i]));
		}
	return (btin_exsign_numeric(pos));
}

int					btin_exsign_numeric(t_ltree *pos)
{
	int				num;
	int				count;
	int				temp;
	
	num = ft_atoi(&pos->ar_v[0][1]);
	if (num < 0)
	{
		count = btin_fc_negative_int__exec(num);
		if (count == 0 && num != 0)
			return (btin_exsign_print_message(pos->ar_v[0]));
	}
	else
	{
		temp = g_hist.last_fc - ((g_hist.last + 1 == g_hist.len) ?
			g_hist.len - 1 : g_hist.last) + 1;
		temp += (temp < 1) ? HISTORY_LIMIT : 0;
		count = btin_fc_positive_int__exec(num, temp, g_hist.last_fc);
		if (count == -2 || (count == g_hist.last && num - 1 != g_hist.last))
			return (btin_exsign_print_message(pos->ar_v[0]));
	}
	return (btin_exsign_make_substitution(pos, g_hist.hist[count]));
}

int					btin_exsign_print_message(char *arg)
{
	ft_putstr_fd(find_env_value("0"), STDOUT_FILENO);
	ft_putstr_fd(": ", STDOUT_FILENO);
	ft_putstr_fd(arg, STDOUT_FILENO);
	ft_putendl_fd(": event not found", STDOUT_FILENO);
	return (0);
}

int					btin_exsign_make_substitution(t_ltree *pos, char *subst)
{
	return (0);
}