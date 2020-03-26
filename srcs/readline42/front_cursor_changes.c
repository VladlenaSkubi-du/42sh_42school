/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   front_cursor_changes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 16:59:26 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/26 18:12:43 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

/*
** @pos_x is absolute calculation of position you have NOW,
** because changes will be visible in global structure @g_rline
** g_rline.pos should be changed after the call of these functions
*/

int					front_move_one_char_right(int pos_x)
{
	if (pos_x < g_screen.ws_col - 1 && g_rline.cmd[g_rline.pos] != '\n')
	{
		tputs(g_cap.nd, 1, printc);
		g_rline.pos_x++;
	}
	else if (pos_x == g_screen.ws_col - 1 ||
		g_rline.cmd[g_rline.pos] == '\n')
	{
		tputs(g_cap.cr, 1, printc);
		tputs(g_cap.dow, 1, printc);
		g_rline.pos_x = 0;
		g_rline.pos_y++;
	}
	return (0);
}

int					front_move_one_char_left(int pos_x)
{
	int				prev_x;

	prev_x = 0;
	if (pos_x > 0)
	{
		tputs(g_cap.le, 1, printc);
		g_rline.pos_x--;
	}
	else if (pos_x == 0)
	{
		if (g_rline.pos > 0 &&
			g_rline.cmd[g_rline.pos - 1] == '\n')
			prev_x = count_x_position_new_line(g_rline.pos - 2);
		else
			prev_x = g_screen.ws_col - 1;
		position_cursor("ch", 0, prev_x);
		tputs(g_cap.up, 1, printc);
		g_rline.pos_x = prev_x;
		g_rline.pos_y--;
	}
	return (0);
}

int					front_insert_by_letters(char *str, int *pos_x, char flag)
{
	size_t			i;

	i = 0;
	while (str[i])
	{
		front_insert_one_char(str[i], *pos_x, 'c', NULL);
		(*pos_x) = i;
		if (*pos_x == g_screen.ws_col - 1)
			*pos_x = 0;
		i++;
	}
	return (0);
}

int					front_write_one_char(char c, char *color)
{
	if (color != NULL)
	{
		write(STDOUT_FILENO, color, ft_strlen(color));
		write(STDOUT_FILENO, &c, 1);
		write(STDOUT_FILENO, DEFAULT, ft_strlen(DEFAULT));
	}
	else
		write(STDOUT_FILENO, &c, 1);
	return (0);
}
