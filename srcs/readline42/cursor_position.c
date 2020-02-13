/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 17:07:05 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/13 19:41:09 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int					position_relative(unsigned short *x,
						unsigned short *y, size_t analyse)
{
	size_t			i;
	unsigned short	j;
	unsigned short	k;
	int				flag;

	i = 0;
	j = g_rline.prompt_len;
	k = 1;
	while (i < analyse && i < g_rline.cmd_len)
	{
		flag = 0;
		if (j == g_screen.ws_col - 1)
		{
			j = -1;
			k++;
			flag = 1;
		}
		j++;
		i++;
		if (i > 0 && g_rline.cmd[i - 1] == '\n' && flag == 0)
		{
			j = 0;
			k++;
		}
	}
	(x) ? *x = j : 0;
	(y) ? *y = k : 0;
	return (0);
}

int					move_cursor_back_after_print(short flag)
{
	size_t			tmp;
	unsigned short	new_x;
	unsigned short	new_y;
	unsigned short	end_x;

	tmp = 0;
	if (g_rline.pos == g_rline.cmd_len)
		return (0);
	position_relative(&new_x, &new_y, g_rline.pos);
	if (flag == 0)
	{
		// if (g_rline.cmd_len + g_rline.prompt_len ==
		// g_screen.ws_col * g_rline.str_num)
		position_relative(&end_x, 0, g_rline.cmd_len - 1);
		if (end_x == g_screen.ws_col - 1)
		{
			putcap("sf");
			tmp = 1;
		}
	}
	position_cursor("ch", 0, new_x);
	if (g_rline.str_num + tmp - new_y == 1)
		putcap("up");
	else if (g_rline.str_num + tmp - new_y > 1)
		position_cursor("UP", 0, g_rline.str_num + tmp - new_y);
	return (0);
}

/*
** @direction can be left = 'l' or right = 'r'
*/

int					move_cursor_from_old_position(size_t pos_old,
						char direction)
{
	unsigned short	new_x;
	unsigned short	new_y;
	unsigned short	old_y;

	position_relative(0, &old_y, pos_old);
	position_relative(&new_x, &new_y, g_rline.pos);
	if (direction == 'l')
	{
		if (old_y - new_y == 1)
			putcap("up");
		else if (old_y - new_y > 1)
			position_cursor("UP", 0, old_y - new_y);
	}
	else
	{
		if (new_y - old_y == 1)
			putcap("do");
		else if (new_y - old_y > 1)
			position_cursor("DO", 0, new_y - old_y);
	}
	position_cursor("ch", 0, new_x);
	return (0);
}

// int					count_line_width()