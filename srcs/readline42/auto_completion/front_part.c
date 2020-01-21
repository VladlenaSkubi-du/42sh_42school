/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   front_part.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 15:46:39 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/21 19:51:31 by sschmele         ###   ########.fr       */
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
*/

int					print_menu(size_t pos_back, char **menu,
						size_t total, int max_len)
{
	t_completion	menu_buf;
	unsigned short	len_x;
	size_t			i;

	i = -1;
	position_relative(&len_x, 0, g_rline.cmd_len);
	position_cursor_for_menu(g_rline.cmd_len);
	menu_buf = menu_buf_init(total, max_len);
	if (g_screen.ws_row - g_rline.str_num >= menu_buf.buf_lines)
	{
		while (++i < menu_buf.word_nb)
			if (menu[i] && menu[i][0] && !(menu[i][0] == '.'))
				buffer_col_print(menu[i], &menu_buf);
		position_cursor_after_menu_back(len_x, menu_buf.buf_lines,
			pos_back, g_rline.cmd_len);
		return (0);
	}
	if (ask_output(total, menu_buf.buf_lines, pos_back, len_x) == 1)
		return (1);
	while (++i < menu_buf.word_nb)
		if (menu[i] && menu[i][0])
			buffer_col_print(menu[i], &menu_buf);
	after_big_menu(pos_back, len_x);
	return (0);
}

/*
** After printing some kind of big menu (the number of lines is bigger
** than the space left in the terminal) the behavior is as in bash - 
** printing new prompt and the line without any changes
*/

int					after_big_menu(size_t pos_back, unsigned short len_x)
{
	putcap("sf");
	g_rline.pos = 0;
	position_cursor("ch", 0, 0);
	g_rline.pos = pos_back;
	g_prompt.prompt_func();
	ft_putstr_fd(g_rline.cmd, 1);
	move_cursor_back_after_print(0);
	g_rline.flag &= ~TAB;
	g_rline.flag &= ~MENU;
	return (0);
}

/*
** After any key except of TAB is pushed, the menu under the line
** is cleared
*/

int					clean_menu(void)
{
	size_t			pos_back;

	pos_back = g_rline.pos;
	position_cursor_for_menu(g_rline.cmd_len);
	putcap("cd");
	putcap("up");
	g_rline.pos = pos_back;
	move_cursor_from_old_position(g_rline.cmd_len, 'l');
	return (0);
}
