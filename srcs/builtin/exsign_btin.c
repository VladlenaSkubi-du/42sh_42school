
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

	i = -1;
	while (++i < (size_t)pos->l_tline.len &&
			!btin_exsign_stop_signs(pos->l_tline.line[i]))
	{
		if (pos->l_tline.line[i] == BANG &&
				(pos->l_tline.line[i + 1] == BANG ||
				pos->l_tline.line[i + 1] == WORD_P ||
				pos->l_tline.line[i + 1] == TEXT))
			return (btin_exsign_start_substitution(pos, i));
		else if (pos->l_tline.line[i] == BANG)
		{
			pos->err_i = i + 1;
			pos->flags |= (ERR_OUT | ERR_R | ERR_REDIR << 16);
			return (ERR_OUT | ERR_R);
		}
	}
	return (0);
}

int					btin_exsign_start_substitution(t_ltree *pos, int i)
{
	int				start;

	if (g_hist.len > 0)
		delete_last_history_element();
	start = i + 1;
	while (pos->l_tline.line[++i] &&
			!btin_exsign_stop_signs(pos->l_tline.line[i]))
		;
	return ((g_hist.last < 0) ?
		btin_exsign_print_message(pos->l_cmd + start - 1, i - start) :
		btin_exsign_route_substitution(pos, start, i));
}

int					btin_exsign_route_substitution(t_ltree *pos,
						int start, int i)
{
	char			*find;
	int				count;
	int				len_num;
	
	if (pos->l_tline.line[start] == BANG)
		return (btin_exsign_make_substitution(pos, start - 1, i,
			g_hist.hist[g_hist.last]));
	len_num = (pos->l_cmd[start] == '-') ? 1 : 0;
	while (start + len_num < i && (pos->l_cmd[start + len_num] >= '0' &&
			pos->l_cmd[start + len_num] <= '9'))
		len_num++;
	if (start + len_num == i)
		return (btin_exsign_numeric(pos, start, i));
	find = ft_strndup(pos->l_cmd + start, i - start);
	if ((count = find_in_history(find)) == -1)
		btin_exsign_print_message(pos->l_cmd + start - 1, i - start);
	else
		btin_exsign_make_substitution(pos, start - 1,
			i, g_hist.hist[count]);
	free(find);
	return ((count == -1) ? ERR_OUT : 0);
}

int					btin_exsign_numeric(t_ltree *pos,
						int start, int end)
{
	int				num;
	int				count;
	int				temp;
	
	num = ft_atoi(pos->l_cmd + start);
	if (num < 0)
	{
		count = btin_fc_negative_int__exec(num);
		if (count == 0 && num != 0)
			return (btin_exsign_print_message(pos->l_cmd + start - 1, end));
	}
	else
	{
		temp = g_hist.last_fc - ((g_hist.last + 1 == g_hist.len) ?
			g_hist.len - 1 : g_hist.last) + 1;
		temp += (temp < 1) ? HISTORY_LIMIT : 0;
		count = btin_fc_positive_int__exec(num, temp, g_hist.last_fc, 0);
		if (count == -2 || (count == g_hist.last && num - 1 != g_hist.last))
			return (btin_exsign_print_message(pos->l_cmd + start - 1, end));
	}
	return (btin_exsign_make_substitution(pos, start - 1,
		end, g_hist.hist[count]));
}

int					btin_exsign_print_message(char *arg, int end)
{
	ft_putstr_fd(find_env_value("0"), STDOUT_FILENO);
	ft_putstr_fd(": ", STDOUT_FILENO);
	ft_putnstr_fd(arg, end, STDOUT_FILENO);
	ft_putendl_fd(": event not found", STDOUT_FILENO);
	return (ERR_OUT);
}

int					btin_exsign_stop_signs(char tech)
{
	if (tech == SPACE || tech == ENTER ||
			tech == SCOLON || tech == AND ||
			tech == OPAREN || tech == CPAREN ||
			tech == PIPE || tech == GTHAN ||
			tech == LTHAN || tech == COLON ||
			tech == END_T)
		return (1);
	return (0);
}

/*
** Here we first prepare the line and techline for substitution
** We start with the cmd_line: if starting from start the gap to
** insert new value is not enough or too much - we "stratch" or
** "tighten" it by ft_strshift
** After the gap is ready, we copy the new value there.
** Example:
** str = "line to_change_this_gap line"
**             |                 |
**           start              end
** len(to_change_this_gap) = 18
**    1) new_value = new_value_for_this_gap (len = 22)
**    Result needed: str = "line new_value_for_this_gap line"
** After ft_strshift:
** str = "line 0000to_change_this_gap line" (shift = 22 - 18)
**             |                 |
**           start              end
**    2) new_value = value_to_insert (len = 15)
**    Result needed: str = "line value_to_insert line"
** After ft_strshift:
** str = "line change_this_gap line" (shift = 15 - 18)
**             |                 |
**           start              end
** After cmd_line we correct the techline:
** 1) prepare the buffer so that there is enough memory allocated
** for the new value to be included if there should be "stratch"
** 2) prepare the gap the same as we did with the cmd_line
** 3) insert enum code needed for the whole len
*/

//ft_memset(pos->l_tline.line + start, TEXT, len_subst);

int					btin_exsign_make_substitution(t_ltree *pos,
						int start, int end, char *subst)
{
	int				len_subst;

	len_subst = ft_strlen(subst);
	if (subst[len_subst - 1] == '\n')
		len_subst--;
	shift_cmd_substitution(&pos->l_cmd, start, end, len_subst);
	ft_strncpy(pos->l_cmd + start, subst, len_subst);
	shift_techline_substitution(&pos->l_tline, start, end, len_subst);
	clear_techline(&pos->l_tline);
	ft_get_techline(pos->l_cmd, &pos->l_tline);
	add_to_history(pos->l_cmd);
	ft_putendl_fd(pos->l_cmd, STDOUT_FILENO);
	return (0);
}