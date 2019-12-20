/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_movement_dir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:02:51 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/20 13:05:59 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void				make_movements(t_args *list, int key)
{
	t_args			*underlined;
	struct winsize	sz;
	unsigned int	limit_left;

	underlined = find_list(list, 'u');
	ioctl(1, TIOCGWINSZ, &sz);
	limit_left = sz.ws_col - underlined->len - 2;
	if (key == 4283163)
		underlined = move_up_a(underlined);
	if (key == 4348699)
		underlined = move_down_b(underlined);
	if (key == 4479771 && underlined->x > 0)
		underlined = move_left_d(underlined);
	else if (key == 4479771 && underlined->x == 0)
		bell_sound(underlined);
	if (key == 4414235 && underlined->x < limit_left)
		underlined = move_right_c(underlined);
	else if (key == 4414235 && underlined->x == limit_left)
		bell_sound(underlined);
}

t_args				*move_down_b(t_args *under)
{
	under->underline = 0;
	underline_off();
	check_selected(under->selected);
	position_and_clear_element(under->x, under->y, under->len);
	output_element(under->arg);
	under = under->next;
	under->underline = 1;
	position_and_clear_element(under->x, under->y, under->len);
	check_selected(under->selected);
	underline_on();
	output_element(under->arg);
	return (under);
}

t_args				*move_up_a(t_args *under)
{
	under->underline = 0;
	underline_off();
	check_selected(under->selected);
	position_and_clear_element(under->x, under->y, under->len);
	output_element(under->arg);
	under = under->prev;
	under->underline = 1;
	position_and_clear_element(under->x, under->y, under->len);
	check_selected(under->selected);
	underline_on();
	output_element(under->arg);
	return (under);
}

t_args				*move_right_c(t_args *under)
{
	t_args		*run;

	run = under->next;
	while (run->y != under->y)
		run = run->next;
	if (run == under)
	{
		bell_sound();
		return (run);
	}
	under->underline = 0;
	underline_off();
	check_selected(under->selected);
	position_and_clear_element(under->x, under->y, under->len);
	output_element(under->arg);
	run->underline = 1;
	position_and_clear_element(run->x, run->y, run->len);
	check_selected(run->selected);
	underline_on();
	output_element(run->arg);
	return (run);
}

t_args				*move_left_d(t_args *under)
{
	t_args			*run;

	run = under->prev;
	while (run->y != under->y)
		run = run->prev;
	if (run == under)
	{
		bell_sound();
		return (run);
	}
	under->underline = 0;
	underline_off();
	check_selected(under->selected);
	position_and_clear_element(under->x, under->y, under->len);
	output_element(under->arg);
	run->underline = 1;
	position_and_clear_element(run->x, run->y, run->len);
	check_selected(run->selected);
	underline_on();
	output_element(run->arg);
	return (run);
}
