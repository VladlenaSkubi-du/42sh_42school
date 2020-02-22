/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   front_cursor_changes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 16:59:26 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/22 21:15:31 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int					front_insert_by_letters(char *str)
{
	size_t			i;

	i = 0;
	while (str[i])
	{
		front_insert_one_char(str[i]);
		i++;
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
		if (g_rline.flag & NEW_LINE_TE)
		{
			g_rline.str_num++;
			g_rline.flag &= ~(NEW_LINE_TE);
		}
		g_rline.flag |= NEW_LINE_SY;
		return (0);
	}
	if (g_rline.pos_x == g_screen.ws_col - 1)
	{
		write(STDOUT_FILENO, &c, 1);
		tputs(g_cap.sf, 1, printc);
		g_rline.pos_x = 0;
		g_rline.pos_y++;
		g_rline.flag |= NEW_LINE_TE;
		return (0);
	}
	write(STDOUT_FILENO, &c, 1);
	if (g_rline.pos_x == 0 && !(g_rline.flag & NEW_LINE_SY))
		g_rline.str_num++;
	else if (g_rline.pos_x == 0 && (g_rline.flag & NEW_LINE_SY))
		g_rline.flag &= ~(NEW_LINE_SY);
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

int					front_insert_cmd_till_the_end(void)
{
	size_t			pos_back;
	int				pos_x_back;
	int				pos_y_back;

	while (g_rline.pos != g_rline.cmd_len)
	{
		front_insert_one_char(g_rline.cmd[g_rline.pos]);
		g_rline.pos++;
	}
	front_set_cursor_jmp(&pos_back, &pos_x_back, &pos_y_back, 0);
	move_cursor_from_old_position(pos_back, 'l');
	return (0);
}