#include "shell42.h"
#include "builtin42.h"

/*
** Builtin !: !! is the last history-cmd in the buffer
** !word is the last history-cmd that starts with word
** !number is the history-cmd according to the number
** !-number is the history-cmd of the same number if count from
** the last cmd
*/

//Добавить error:
// bash-3.2$ !
// bash: syntax error near unexpected token `newline'

int					btin_exsign(t_ltree *pos)
{
	int				i;

	if (g_hist.len < 1 || g_hist.last < 0)
		return (btin_exsign_print_message(pos->ar_v[0]));
	i = -1;
	while (++i < pos->l_tline.len)
	{
		if (pos->l_tline.line[i] == BANG &&
				pos->l_tline.line[i + 1] == BANG)
			return (btin_exsign_make_substitution(pos, i,
				g_hist.hist[g_hist.last]));
		else if (pos->l_tline.line[i] == BANG &&
				(pos->l_tline.line[i + 1] == WORD_P ||
				pos->l_tline.line[i + 1] == TEXT))
			return (btin_exsign_route_substitution(pos, i));
		else if (pos->l_tline.line[i] == BANG &&
				(pos->l_tline.line[i + 1] == ENTER ||
				pos->l_tline.line[i + 1] == END_T))
			return (-2);
	}
	return (0);
}

int					btin_exsign_route_substitution(t_ltree *pos, int i)
{
	int				start;
	int				numeric;
	char			*find;
	
	numeric = 1;
	if (pos->l_cmd[i] == '-')
		i++;
	start = i + 1;
	while (pos->l_tline.line[++i] == WORD_P ||
			pos->l_tline.line[i] == TEXT)
		if (!(pos->l_cmd[i] >= '0' && pos->l_cmd[i] <= '9'))
			numeric = 0;
	find = ft_strndup(pos->l_cmd + start, i - start);
	if (numeric == 1)
		btin_exsign_numeric(pos, start, find);
	else
	{
		if ((i = find_in_history(find)) == -1)
			btin_exsign_print_message(find);
		else
			btin_exsign_make_substitution(pos, start - 1, g_hist.hist[i]);
	}
	free(find);
	return (0);
}

int					btin_exsign_numeric(t_ltree *pos,
						int start, char *find)
{
	int				num;
	int				count;
	int				temp;
	
	num = ft_atoi(find);
	if (num < 0)
	{
		count = btin_fc_negative_int__exec(num);
		if (count == 0 && num != 0)
			return (btin_exsign_print_message(find));
	}
	else
	{
		temp = g_hist.last_fc - ((g_hist.last + 1 == g_hist.len) ?
			g_hist.len - 1 : g_hist.last) + 1;
		temp += (temp < 1) ? HISTORY_LIMIT : 0;
		count = btin_fc_positive_int__exec(num, temp, g_hist.last_fc);
		if (count == -2 || (count == g_hist.last && num - 1 != g_hist.last))
			return (btin_exsign_print_message(find));
	}
	return (btin_exsign_make_substitution(pos, start - 1, g_hist.hist[count]));
}

int					btin_exsign_print_message(char *arg)
{
	ft_putstr_fd(find_env_value("0"), STDOUT_FILENO);
	ft_putstr_fd(": ", STDOUT_FILENO);
	ft_putstr_fd(arg, STDOUT_FILENO);
	ft_putendl_fd(": event not found", STDOUT_FILENO);
	return (0);
}

int					btin_exsign_make_substitution(t_ltree *pos,
						int start, char *subst)
{
	return (0);
}