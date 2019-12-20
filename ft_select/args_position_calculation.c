/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_position_calculation.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:33:08 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/20 13:04:39 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void				fill_in_position(t_args *list, int term_lines, int max_len)
{
	t_args			*run;
	size_t			i;
	size_t			j;

	run = list;
	i = 0;
	j = 0;
	while (run->next != list)
	{
		run = run->next;
		run->x = i;
		run->y = ++j;
		if (max_len != 0)
		{
			if (j == (size_t)term_lines - 1)
			{
				i += max_len;
				j = -1;
			}
		}
	}
}

int					calculate_position(t_args *list, int total, size_t max_len)
{
	struct winsize	sz;
	int				max_columns;
	int				max_capability;

	ioctl(1, TIOCGWINSZ, &sz);
	max_columns = sz.ws_col / max_len;
	max_capability = max_columns * sz.ws_row;
	if (total > max_capability)
		return (-1);
	if (total <= sz.ws_row)
		fill_in_position(list, 0, 0);
	else
		fill_in_position(list, sz.ws_row, max_len);
	return (1);
}

/*
** If args_total == 1, it means that we make "DELETE with |_X_>" delete the
** last element (the next one is the beginning *list because we have
** the cycled structure) and we do not need to make reposition
*/

t_args				*reposition_till_the_end(t_args *list, t_args *first_after)
{
	int				total;
	size_t			i;
	t_args			*run;

	total = args_total(list, first_after);
	if (total == 1 && list == first_after)
		return (first_after);
	i = 0;
	run = list->prev;
	while (i <= (size_t)total)
	{
		position_and_clear_element(run->x, run->y, run->len);
		run->x = run->prev->x;
		run->y = run->prev->y;
		run = run->prev;
		i++;
	}
	return (first_after);
}
