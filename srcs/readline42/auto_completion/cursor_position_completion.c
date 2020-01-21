/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_position_completion.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 16:51:01 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/21 19:52:33 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int					position_cursor_for_menu(size_t len)
{
	size_t			pos_old;

	g_rline.flag |= MENU;
	pos_old = g_rline.pos;
	if (g_rline.pos == 0 && len == 0)
		putcap("sf");
	else
	{
		g_rline.pos = len;
		move_cursor_from_old_position(pos_old, 'r');
		if (g_rline.pos + g_rline.prompt_len <
			g_screen.ws_col * g_rline.str_num)
			putcap("sf");
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
