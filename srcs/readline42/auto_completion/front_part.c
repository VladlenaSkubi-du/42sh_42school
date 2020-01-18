/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   front_part.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 15:46:39 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/17 16:26:34 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

/*
** The front-part: we put cursor to the end of the line -
** only within the line we can use functions from cursor_position.c file
** because they use g_rline.pos - after that we print the menu-buffer
** and put the cursor back to the end of the cmd-line
** and back to the old position
**
** @menu_lines_num we need to understand how high we need to jump
** to the end of the cmd-line after the menu-printing
**
** The back-part: menu-buffer is filled in in the output_buffer.c file
*/

int					print_menu(size_t len, size_t pos_back,
						char pool, char *complete)
{
	char			**menu = NULL;
	t_completion	menu_buf;
	unsigned short	len_x;
	static int		tab_push;
	size_t			i;

	tab_push = (g_rline.flag & TAB) ? tab_push + 1 : -1;
	g_rline.flag |= TAB;
	i = -1;
	position_relative(&len_x, 0, len);
	position_cursor_for_menu(len);
	menu_buf_init(&menu_buf);
	// menu = get_menu(pool, &menu_buf);
	while (++i < menu_buf.word_nb)
		buffer_col_print(menu[i], &menu_buf);
	position_cursor_after_menu_back(len_x, menu_buf.buf_lines, pos_back, len);
	return (0);
}

int					clean_menu(void)
{
	size_t			pos_back;

	pos_back = g_rline.pos;
	position_cursor_for_menu(g_rline.cmd_len);
	putcap("cd");
	g_rline.pos = pos_back;
	move_cursor_from_old_position(g_rline.cmd_len, 'l');
	return (0);
}