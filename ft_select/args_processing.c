/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_processing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:25:47 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/20 13:05:06 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int				args_total(const t_args *list, const t_args *under)
{
	t_args		*run;
	int			total;

	run = (t_args*)under;
	total = 0;
	while (run->next != list)
	{
		total++;
		run = run->next;
	}
	return (total + 1);
}

void			output_arguments(const t_args *list, const t_args *under)
{
	t_args		*run;
	int			total;
	size_t		i;

	if (list == NULL)
		return ;
	run = (t_args*)under;
	total = args_total((const t_args*)list, under);
	i = 0;
	while (i < (size_t)total)
	{
		if (run->selected == 1)
			inverse_video_on();
		else
			inverse_video_off();
		if (run->underline == 1)
			underline_on();
		else
			underline_off();
		position_cursor(run->x, run->y);
		ft_putstr_fd(run->arg, 2);
		i++;
		run = run->next;
	}
}

t_args			*find_list(t_args *list, char flag)
{
	t_args		*needed;

	needed = list;
	if (flag == 'u')
	{
		while (needed->underline != 1)
			needed = needed->next;
	}
	return (needed);
}

t_args			*delete_argument(t_args *list, t_args *selected)
{
	t_args		*save;
	int			total;

	save = selected->next;
	total = args_total(list, selected);
	if (list == selected && total == 1)
	{
		free(selected->arg);
		free(selected);
		return (NULL);
	}
	else if (list->next == selected && list->prev == selected)
	{
		list->next = list;
		list->prev = list;
	}
	else
	{
		selected->prev->next = save;
		save->prev = selected->prev;
	}
	free(selected->arg);
	free(selected);
	save->underline = 1;
	return (save);
}

void			free_arguments(t_args *list)
{
	t_args		*run;

	run = list;
	while (run != NULL)
		run = delete_argument(list, list->next);
}
