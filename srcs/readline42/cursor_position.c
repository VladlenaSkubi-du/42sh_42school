/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 17:07:05 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/10 19:02:21 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

// unsigned int		on_which_line(size_t cmd_pos, unsigned short col)
// {
// 	unsigned int	i;

// 	i = 1;
// 	while (cmd_pos >= col * i || (g_rline.cmd[cmd_pos - 1] &&
// 		g_rline.cmd[cmd_pos - 1] == '\n'))
// 		i++;
// 	return (i);
// }

int					position_relative(unsigned short *x,
						unsigned short *y, size_t analyse)
{
	size_t			i;
	unsigned short	j;
	unsigned short	k;

	i = 0;
	j = g_rline.prompt_len;
	k = 1;
	while (i < analyse && i < g_rline.cmd_len)
	{
		if ((g_rline.cmd[i] && g_rline.cmd[i] == '\n') ||
			j == g_screen.ws_col - 1)
		{
			j = -1;
			k++;
		}
		j++;
		i++;
	}
	(x) ? *x = j : 0;
	(y) ? *y = k : 0;
	return (0);
}

// int					position_relative(unsigned short *x,
// 						unsigned short *y, size_t analyse)
// {
// 	if (g_rline.prompt_len + analyse < g_screen.ws_col)
// 	{
// 		(x) ? *x = g_rline.prompt_len + analyse : 0;
// 		(y) ? *y = 1 : 0;
// 	}
// 	else
// 	{
// 		(x) ? *x = (g_rline.prompt_len + analyse) % g_screen.ws_col : 0;
// 		(y) ? *y = on_which_line(g_rline.prompt_len + analyse,
// 			g_screen.ws_col) : 0;
// 	}
// 	return (0);
// }

int					move_cursor_back_after_print(short flag)
{
	size_t			tmp;
	unsigned short	new_x;
	unsigned short	new_y;

	tmp = 0;
	if (flag == 0)
	{
		if (g_rline.cmd_len + g_rline.prompt_len ==
		g_screen.ws_col * g_rline.str_num)
		{
			putcap("sf");
			tmp = 1;
		}
	}
	position_relative(&new_x, &new_y, g_rline.pos);
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
