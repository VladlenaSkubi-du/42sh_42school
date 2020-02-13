/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_position_completion.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 16:51:01 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/13 18:00:45 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int					position_cursor_for_menu(size_t len)
{
	size_t			pos_old;
	unsigned short	end_x;


	pos_old = g_rline.pos;
	if (g_rline.pos == 0 && len == 0)
		putcap("sf");
	else
	{
		g_rline.pos = len;
		move_cursor_from_old_position(pos_old, 'r');
		position_relative(&end_x, 0, g_rline.pos);
		if (end_x < g_screen.ws_col)
			putcap("sf");
		// if (g_rline.pos + g_rline.prompt_len <
		// 	g_screen.ws_col * g_rline.str_num)
	}
	return (0);
}

int					position_cursor_after_menu_back(unsigned short len_x,
						int buf_lines, size_t pos_back, size_t len)
{
	size_t			i;

	i = -1;
	position_cursor("ch", 0, len_x);
	while (++i < buf_lines)
		putcap("sr");
	g_rline.pos = pos_back;
	move_cursor_from_old_position(len, 'l');
	return (0);
}
