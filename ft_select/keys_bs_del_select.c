/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_bs_del_select.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 17:04:30 by sschmele          #+#    #+#             */
/*   Updated: 2019/11/14 15:08:09 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void			select_element(t_args *list)
{
	t_args		*underlined;

	underlined = find_list(list, 'u');
	if (underlined->selected == 0)
	{
		underlined->selected = 1;
		inverse_video_on();
	}
	else
	{
		underlined->selected = 0;
		inverse_video_off();
	}
	position_and_clear_element(underlined->x,
		underlined->y, underlined->len);
	output_element(underlined->arg);
	underlined = move_down_b(underlined);
}

/*
** That is because I use it many times in all the movements
*/

void			check_selected(int under_selected)
{
	if (under_selected == 1)
		inverse_video_on();
	else if (under_selected == 0)
		inverse_video_off();
}

/*
** By pushing backspace: <_X_| you can't delete the last and the first element
** (if it is not the only one) because you delete the previous element you are
** standing on
** If you delete the first element in the menu-list, you need
** to move the beginning of the menu-list - @*list
*/

t_args			*backspace_element(t_args *list)
{
	t_args		*underlined;
	t_args		*tobe_deleted;

	underlined = find_list(list, 'u');
	if (underlined == list && underlined->next != list)
	{
		bell_sound();
		return (list);
	}
	tobe_deleted = underlined->prev;
	underlined = reposition_till_the_end(list, underlined);
	if (tobe_deleted == list)
	{
		underlined = delete_argument(list, tobe_deleted);
		list = underlined;
	}
	else
		underlined = delete_argument(list, tobe_deleted);
	if (list != NULL)
		output_arguments(list, underlined);
	return (list);
}

/*
** By pushing delete: |_X_> you can delete elements from all the
** positions because you delete an element you are standing on
** If you delete the first element in the menu-list, you need
** to move the beginning of the menu-list - @*list
*/

t_args			*delete_element(t_args *list)
{
	t_args		*underlined;
	t_args		*next_after;

	underlined = find_list(list, 'u');
	next_after = underlined->next;
	if (next_after != list)
		next_after = reposition_till_the_end(list, next_after);
	else
		position_and_clear_element(underlined->x,
			underlined->y, underlined->len);
	if (underlined == list)
	{
		underlined = delete_argument(list, underlined);
		list = underlined;
	}
	else
		underlined = delete_argument(list, underlined);
	if (list != NULL)
		output_arguments(list, underlined);
	return (list);
}
