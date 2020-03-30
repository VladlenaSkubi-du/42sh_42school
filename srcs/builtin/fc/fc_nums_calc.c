#include "shell42.h"
#include "builtin42.h"

int				btin_fc_two_ints__list(t_btin_fc **fc_arg, int *flags)
{
	int			temp;

	temp = g_hist.last_fc - ((g_hist.last + 1 == g_hist.len) ?
		g_hist.len - 1 : g_hist.last) + 1;
	if (((*fc_arg)->flag & ARG_SECOND) && (*fc_arg)->last > 0)
	{
		if (((*fc_arg)->last_buf = btin_fc_positive_int__list
			((*fc_arg)->last, temp, g_hist.last_fc)) == HIST_ERROR)
			return (HIST_ERROR);
	}
	else if ((*fc_arg)->flag & ARG_SECOND)
		(*fc_arg)->last_buf = btin_fc_negative_int__list((*fc_arg)->last);
	if (((*fc_arg)->flag & ARG_FIRST) && (*fc_arg)->first > 0)
	{
		if (((*fc_arg)->first_buf = btin_fc_positive_int__list
			((*fc_arg)->first, temp, g_hist.last_fc)) == HIST_ERROR)
			return (HIST_ERROR);
	}
	else if ((*fc_arg)->flag & ARG_FIRST)
		(*fc_arg)->first_buf = btin_fc_negative_int__list((*fc_arg)->first);
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

int				btin_fc_negative_int__list(int value)
{
	int			final_buf;

	final_buf = g_hist.last;
	if (value <= 0)
	{
		value = (value == 0) ? -1 : value;
		final_buf += value;
		if (final_buf < 0)
			final_buf = 0;
	}
	return (final_buf);
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

int				btin_fc_negative_int__exec(int value)
{
	int			final;

	final = g_hist.last;
	value = (value == 0) ? -1 : value;
	final += value + 1;
	if (final < 0)
		final = 0;
	return (final);
}