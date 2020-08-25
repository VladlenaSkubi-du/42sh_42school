/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump_around.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 18:48:41 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/25 20:39:11 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int			ctrl_up_jumplineup(void)
{
	int			pos_x_goal;

	if (g_rline.str_num < 2 || g_rline.pos_y == 0)
		return (incorrect_sequence());
	pos_x_goal = g_rline.pos_x;
	while (g_rline.pos_x != 0 && g_rline.pos)
		arrow_left_jumpcharleft();
	if (g_rline.pos_x == 0)
	{
		arrow_left_jumpcharleft();
		if (g_rline.pos_y == 0 && g_rline.pos_x >
			pos_x_goal + g_prompt.prompt_len)
		{
			while (g_rline.pos_x != pos_x_goal + g_prompt.prompt_len
				&& g_rline.pos)
				arrow_left_jumpcharleft();
		}
		else if (g_rline.pos_y > 0 && g_rline.pos_x > pos_x_goal)
		{
			while (g_rline.pos_x != pos_x_goal && g_rline.pos)
				arrow_left_jumpcharleft();
		}
	}
	return (0);
}

int			ctrl_down_jumplinedown(void)
{
	int			pos_x_goal;
	int			flag;

	if (g_rline.str_num < 2 || g_rline.pos_y == g_rline.str_num - 1)
		return (incorrect_sequence());
	pos_x_goal = (g_rline.pos_y == 0) ? g_rline.pos_x - g_prompt.prompt_len :
		g_rline.pos_x;
	flag = (pos_x_goal == 0) ? 1 : 0;
	if (pos_x_goal == 0)
		arrow_right_jumpcharright();
	while (g_rline.pos_x != 0)
		arrow_right_jumpcharright();
	if (g_rline.pos_x == 0 && (pos_x_goal > 0 || flag == 1))
	{
		arrow_right_jumpcharright();
		if (flag == 1)
			return (arrow_left_jumpcharleft());
		while (g_rline.pos_x < pos_x_goal && g_rline.pos_x != 0 &&
			g_rline.pos < g_rline.cmd_len)
			arrow_right_jumpcharright();
		(g_rline.pos_x == 0) ? arrow_left_jumpcharleft() : 0;
	}
	return (0);
}

int			ctrl_a_jumplinebeg(void)
{
	int				pos_old;

	check_after_line();
	if (g_rline.cmd_len == 0 || g_rline.pos <= 0
			|| g_rline.pos > g_rline.cmd_len)
		return (0);
	pos_old = 0;
	move_cursor_from_old_position(pos_old, 'l');
	return (0);
}

int			ctrl_e_jumplineend(void)
{
	int				pos_old;

	check_after_line();
	if (g_rline.cmd_len == 0 || g_rline.pos < 0
			|| g_rline.pos > g_rline.cmd_len)
		return (0);
	pos_old = g_rline.cmd_len - 1;
	if (g_rline.pos < g_rline.cmd_len)
		move_cursor_from_old_position(pos_old, 'r');
	else
		move_cursor_from_old_position(pos_old, 'l');
	return (0);
}
