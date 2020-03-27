#include "shell42.h"
#include "builtin42.h"

int				btin_fc_two_ints__list(t_btin_fc **fc_arg, int *flags)
{
	int			temp;

	temp = g_hist.last_fc - (g_hist.len - 1) + 1;
	if (((*fc_arg)->flag & ARG_SECOND) && (*fc_arg)->last > 0)
	{
		if (((*fc_arg)->last_buf = btin_fc_positive_int__list
			((*fc_arg)->last, temp, g_hist.last_fc)) == HIST_ERROR)
			return (HIST_ERROR);
	}
	else if ((*fc_arg)->flag & ARG_SECOND)
		(*fc_arg)->last_buf = btin_fc_one_int__edit((*fc_arg)->last);
	if (((*fc_arg)->flag & ARG_FIRST) && (*fc_arg)->first > 0)
	{
		if (((*fc_arg)->first_buf = btin_fc_positive_int__list
			((*fc_arg)->first, temp, g_hist.last_fc)) == HIST_ERROR)
			return (HIST_ERROR);
	}
	else if ((*fc_arg)->flag & ARG_FIRST)
		(*fc_arg)->first_buf = btin_fc_one_int__edit((*fc_arg)->first);
	temp += (temp < 1) ? HISTORY_LIMIT : 0;
	(*fc_arg)->last = ((*fc_arg)->flag & ARG_SECOND) ?
		btin_fc_calculate_nums__list((*fc_arg)->last_buf, temp) : 0;
	(*fc_arg)->first = ((*fc_arg)->flag & ARG_FIRST) ?
		btin_fc_calculate_nums__list((*fc_arg)->first_buf, temp) : 0;
	return (0);
}

int				btin_fc_positive_int__list(int value, int from,
					int to)
{
	int			final;

	if (value > HISTORY_LIMIT)
		return (g_hist.last - 1);
	if ((from > to && !((value >= 1 && value < to) ||
		(value >= from && value <= HISTORY_LIMIT))) ||
		(from < to && !(value >= from)) || (from == to))
	{
		error_handler(VARIABLE_ERROR | (ERR_HISTORY_NUM << 9), "fc");
		return (HIST_ERROR);
	}
	final = value;
	if (from > to)
		final = value + HISTORY_LIMIT - from;
	else if (from < to && value < to)
		final = value - from;
	else if (from < to)
		final = g_hist.last - 1;
	return (final);
}

int				btin_fc_calculate_nums__list(int buffer, int from)
{
	int			value;
	int			tmp;

	tmp = buffer + from;
	if (tmp > HISTORY_LIMIT)
		value = tmp - HISTORY_LIMIT;
	else
		value = tmp;
	return (value);
}

int				btin_fc_one_int__exec(t_btin_fc **fc_arg)
{
	int			temp;
	int			tmp;

	temp = g_hist.last_fc - (g_hist.len - 1) + 1;
	if ((*fc_arg)->first > 0)
	{
		if (((*fc_arg)->first_buf = btin_fc_positive_int__exec
			((*fc_arg)->first, temp, g_hist.last_fc)) == HIST_ERROR)
			return (HIST_ERROR);
	}
	else
	{
		(*fc_arg)->first_buf = g_hist.last;
		tmp = (*fc_arg)->first;
		tmp = (tmp == 0) ? -1 : tmp;
		(*fc_arg)->first_buf += tmp + 1;
		if ((*fc_arg)->first_buf < 0)
			(*fc_arg)->first_buf = 0;
	}
	return (0);
}

int				btin_fc_positive_int__exec(int value, int from,
					int to)
{
	int			final;

	if (value > HISTORY_LIMIT)
		return (g_hist.last);
	if ((from > to && !((value >= 1 && value < to) ||
		(value >= from && value <= HISTORY_LIMIT))) ||
		(from < to && !(value >= from)) || (from == to))
	{
		error_handler(VARIABLE_ERROR | (ERR_HISTORY_NUM << 9), "fc");
		return (HIST_ERROR);
	}
	final = value;
	if (from > to)
		final = value + HISTORY_LIMIT - from;
	else if (from < to && value < to)
		final = value - from;
	else if (from < to)
		final = g_hist.last;
	return (final);
}