/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_nums_calc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 13:14:03 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/16 19:36:20 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

int					btin_fc_one_int__edit(int value)
{
	int				final_buf;

	final_buf = g_hist.last;
	if (value <= 0)
	{
		value = (value == 0) ? -1 : value;
		final_buf += value;
		if (final_buf < 0)
			final_buf = 0;
	}
	else if (value > 0)
	{
		if (value - 1 > 0 && value - 1 < g_hist.last)
			final_buf = value - 1;
	}
	return (final_buf);
}

int					btin_fc_two_ints__edit(t_btin_fc **fc_arg)
{
	t_btin_fc		*tmp;

	tmp = *fc_arg;
	if (!((tmp->flag & ARG_FIRST) && (tmp->flag & ARG_SECOND)))
		return (0);
	tmp->last_buf = btin_fc_one_int__edit(tmp->last);
	tmp->first_buf = btin_fc_one_int__edit(tmp->first);
	return (0);
}

int					btin_fc_two_ints__list(t_btin_fc **fc_arg)
{
	t_btin_fc		*tmp;
	int             temp;

	tmp = *fc_arg;
	temp = g_hist.last_fc - (g_hist.len - 1) + 1;
	if (tmp->last > 0)
	{
		if ((tmp->last_buf = btin_fc_positive_int__list
			(tmp->last, temp, g_hist.last_fc, 'l')) == HIST_ERROR)
			return (HIST_ERROR);
	}
	else
		tmp->last_buf = btin_fc_one_int__edit(tmp->last);
	if (tmp->first > 0)
	{
		if ((tmp->first_buf = btin_fc_positive_int__list
			(tmp->first, temp, g_hist.last_fc, 'f')) == HIST_ERROR)
			return (HIST_ERROR);
	}
	else
		tmp->first_buf = btin_fc_one_int__edit(tmp->first);
	temp += (temp < 1) ? HISTORY_LIMIT : 0;
	tmp->last = btin_fc_calculate_nums__list(tmp->last_buf, temp);
	tmp->first = btin_fc_calculate_nums__list(tmp->first_buf, temp);
	return (0);
}

int				btin_fc_positive_int__list(int value, int from,
					int to, char flag)
{
	int			final;

	if (value > HISTORY_LIMIT && flag == 'l')
		return (g_hist.last);
	else if (value > HISTORY_LIMIT && flag == 'f')
		return (0);
	if ((from > to && !((value >= 1 && value < to) ||
		(value >= from && value <= HISTORY_LIMIT))) ||
		(from < to && !(value >= from && value < to)) || (from == to))
	{
		error_handler(VARIABLE_ERROR | (ERR_HISTORY << 9), "fc");
		return (HIST_ERROR);
	}
	final = value;
	if (from > to)
		final = value + HISTORY_LIMIT - from;
	else if (from < to)
		final = value - from;
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