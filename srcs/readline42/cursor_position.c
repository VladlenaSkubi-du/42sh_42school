/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 17:07:05 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/20 18:35:53 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int					change_xy_by_terminal(int *xx, int *yy, size_t *i)
{
	if (*xx < g_screen.ws_col - 1)
        (*xx)++;
    else
    {
        *xx = 0;
        (*yy)++;
    }
	(*i)++;
	return (0);
}

int					position_relative(int *x, int *y, size_t analyse)
{
	size_t			i;
	int				xx;
	int				yy;

	i = 0;
	xx = g_rline.prompt_len;
	yy = 0;
	while (i <= analyse && i < g_rline.cmd_len)
	{
		if (i > 0 && g_rline.cmd[i - 1] == '\n')
        {
            yy++;
            xx = 0;
			i++;
			continue ;
        }
        change_xy_by_terminal(&xx, &yy, &i);
	}
	(x) ? *x = xx : 0;
	(y) ? *y = yy : 0;
	return (0);
}

/*
** @direction can be left = 'l' or right = 'r'
*/

int					move_cursor_from_old_position(size_t pos_old,
						char direction)
{
	size_t			i;

	i = 0;
	if (direction == 'l')
	{
		while (g_rline.pos != pos_old)
		{
			front_move_one_char_left(g_rline.pos_x);
			g_rline.pos--;
		}
	}
	if (direction == 'r')
	{
		while (g_rline.pos != pos_old)
		{
			front_move_one_char_right(g_rline.pos_x);
			g_rline.pos++;
		}
	}
	return (0);
}
