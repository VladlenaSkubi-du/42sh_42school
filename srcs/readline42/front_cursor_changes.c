/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   front_cursor_changes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 16:59:26 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/20 19:05:09 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

/*
** @Flag == 1 means "save position"
** @flag == 0 means "return position"
*/

int					front_set_cursor_jmp(size_t *pos, int *pos_x,
						int *pos_y, int flag)
{
	static size_t	pos_save;
	static int		pos_x_save;
	static int		pos_y_save;
	
	if (flag == 1)
	{
		pos_save = *pos;
		pos_x_save = *pos_x;
		pos_y_save = *pos_y;
	}
	if (flag == 0)
	{
		*pos = pos_save;
		*pos_x = pos_x_save;
		*pos_y = pos_y_save;
	}
	return (0);
}

/*
** When chars are inserted in the front part, position is changed
** by the terminal automatically - so I increase counters x and y
** after the changes are already done. @g_rline.pos is changed before
** the call of the function - can be also after, no influence
*/

int					front_insert_one_char(char c)
{
	if (c == '\n')
	{
		g_rline.pos_x = 0;
		g_rline.pos_y++;
		g_rline.str_num++;
		write(STDOUT_FILENO, &c, 1);
		return (0);
	}
	if (g_rline.pos_x == g_screen.ws_col - 1)
	{
		write(STDOUT_FILENO, &c, 1);
		tputs(g_cap.sf, 1, printc);
		g_rline.pos_x = 0;
		g_rline.pos_y++;
		return (0);
	}
	write(STDOUT_FILENO, &c, 1);
	if (g_rline.pos_x == 0)
		g_rline.str_num++;
	g_rline.pos_x++;
	return (0);
}

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
	int				enter_x;

	if (pos_x > 0)
	{
		tputs(g_cap.le, 1, printc);
		g_rline.pos_x--;
	}
	else if (pos_x == 0)
	{
		position_relative(&enter_x, 0, g_rline.pos - 1);
		position_cursor("ch", 0, enter_x);
		tputs(g_cap.up, 1, printc);
		g_rline.pos_x = enter_x;
		g_rline.pos_y--;
	}
	return (0);
}

int					front_insert_cmd_till_the_end(void)
{
	int				i;
	size_t			pos_back;
	int				pos_x_back;
	int				pos_y_back;

	i = -1;
	while (g_rline.pos + i != g_rline.cmd_len)
	{
		front_insert_one_char(g_rline.cmd[g_rline.pos + i]);
		g_rline.pos++;
		i++;
	}
	front_set_cursor_jmp(&pos_back, &pos_x_back, &pos_y_back, 0);
	move_cursor_from_old_position(pos_back, 'l');
	return (0);
}