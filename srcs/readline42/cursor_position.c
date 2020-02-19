/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 17:07:05 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/19 17:40:46 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int					position_relative(int *x,
						int *y, size_t analyse)
{
	size_t			i;
	int	j;
	int	k;
	int				flag;

	i = 0;
	j = g_rline.prompt_len;
	k = 1;
	flag = 0;
	while (i < analyse && i < g_rline.cmd_len)
	{
		if (j == g_screen.ws_col - 1 && g_rline.cmd[i] != '\n')
			flag = 1;
		else if (g_rline.cmd[i] == '\n')
			flag = 2;
		j++;
		i++;
		if (flag == 1 || flag == 2)
		{
			((i < analyse && flag == 1) || flag == 2) ? k++ : 0;
			j = 0;
			flag = 0;
		}
	}
	(x) ? *x = j : 0;
	(y) ? *y = k : 0;
	return (0);
}

int					move_cursor_back_after_print(short flag)
{
	size_t			tmp;
	int	new_x;
	int	new_y;
	int	end_x;

	tmp = 0;
	if (g_rline.pos == g_rline.cmd_len)
		return (0);
	position_relative(&new_x, &new_y, g_rline.pos);
	if (flag == 0)
	{
		position_relative(&end_x, 0, g_rline.cmd_len - 1);
		if (end_x == g_screen.ws_col - 1)
			tmp = 1;
	}
	position_cursor("ch", 0, new_x);
	if (new_x == g_screen.ws_col - 1)
		putcap("up");
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
	int	new_x;
	int	new_y;
	int	old_y;

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

int					insert_word_by_letters(char *insert, size_t start)
{
	size_t			i;
	static int		len;

	i = 0;
	if (insert == NULL)
	{
		len = start;
		return (0);
	}
	while (insert[i])
	{
		write(STDOUT_FILENO, &insert[i], 1);
		i++;
		len++;
		if (len == g_screen.ws_col - 1)
		{
			putcap("sf");
			len = -1;
		}
	}
	return (0);
}