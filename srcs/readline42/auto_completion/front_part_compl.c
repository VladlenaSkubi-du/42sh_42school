/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   front_part_compl.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 15:46:39 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/20 20:12:04 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

t_completion		g_menu_buf;

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
	int				len_x;
	int				i;

	i = -1;
	position_relative(&len_x, 0, g_rline.cmd_len);
	position_cursor_for_menu(g_rline.cmd_len);
	g_menu_buf = menu_buf_init(total, max_len);
	if (g_screen.ws_row - g_rline.str_num >= g_menu_buf.buf_lines)
	{
		while (++i < g_menu_buf.word_nb)
			if (menu[i] && menu[i][0])
				buffer_col_print(menu[i], &g_menu_buf);
		position_cursor_after_menu_back(len_x, g_menu_buf.buf_lines,
			pos_back, g_rline.cmd_len);
		g_rline.flag |= TAB;
		return (0);
	}
	if (ask_output(total, g_menu_buf.buf_lines, pos_back, len_x) == 1)
		return (1);
	while (++i < g_menu_buf.word_nb)
		if (menu[i] && menu[i][0])
			buffer_col_print(menu[i], &g_menu_buf);
	after_big_menu(pos_back, len_x);
	return (0);
}

int					print_menu_buf_after_insert(size_t pos_back)
{
	int	len_x;

	position_relative(&len_x, 0, g_rline.cmd_len);
	position_cursor_for_menu(g_rline.cmd_len);
	buffer_col_finish(&g_menu_buf);
	position_cursor_after_menu_back(len_x, g_menu_buf.buf_lines,
		pos_back, g_rline.cmd_len);
	return (0);
}

/*
** After printing some kind of big menu (the number of lines is bigger
** than the space left in the terminal) the behavior is as in bash -
** printing new prompt and the line without any changes
*/

int					after_big_menu(size_t pos_back, int len_x)
{
	tputs(g_cap.sf, 1, printc);
	g_rline.pos = 0;
	position_cursor("ch", 0, 0);
	g_prompt.prompt_func();
	g_rline.pos = pos_back;
	front_insert_cmd_till_the_end();
	// // ft_putstr_fd(g_rline.cmd, 1);
	// insert_word_by_letters(NULL, g_rline.prompt_len);
	// insert_word_by_letters(g_rline.cmd, 0);
	// move_cursor_back_after_print(0);
	g_rline.flag &= ~TAB;
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
	tputs(g_cap.cd, 1, printc);
	tputs(g_cap.up, 1, printc);
	g_rline.pos = pos_back;
	move_cursor_from_old_position(g_rline.cmd_len, 'l');
	clean_menu_buf();
	return (0);
}

int					clean_menu_buf(void)
{
	size_t			i;

	i = -1;
	while (++i < g_menu_buf.buf_lines)
		free(g_menu_buf.buffer[i]);
	free(g_menu_buf.buffer);
	g_menu_buf.buffer = NULL;
	return (0);
}
