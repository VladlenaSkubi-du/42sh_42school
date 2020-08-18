/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_positioning.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 18:54:23 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/09 19:00:21 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

static t_rline_questions	front_for_questions;

/*
** In order to insert something after the cmd-line,
** history or auto-completion, we need to jump to the end
** of the cmd-line and to the next line
*/

int					position_cursor_after_line(int len)
{
	if (g_rline.pos == 0 && len == 0)
		tputs(g_cap.sf, 1, printc);
	else
	{
		move_cursor_from_old_position(len, 'r');
		tputs(g_cap.sf, 1, printc);
	}
	return (0);
}

/*
** In order to clean something after the cmd-line,
** history or auto-completion, we need to jump to the end
** of the cmd-line and to the next line, clear everything
** by the temcap code and move cursor to the position
** it had before clearing
*/

int					clean_after_line(void)
{
	int				pos_back;
	int				len_back;
	int				len_x_back;
	int				len_y_back;

	pos_back = g_rline.pos;
	if (pos_back == 0 && g_rline.cmd_len < 1)
	{
		tputs(g_cap.cd, 1, printc);
		return (0);
	}
	position_cursor_after_line(g_rline.cmd_len);
	front_set_cursor_jmp(&g_rline.pos, &g_rline.pos_x,
		&g_rline.pos_y, 1);
	tputs(g_cap.cd, 1, printc);
	front_set_cursor_jmp(&len_back, &len_x_back, &len_y_back, 0);
	position_cursor("ch", 0, len_x_back);
	tputs(g_cap.up, 1, printc);
	move_cursor_from_old_position(pos_back, 'l');
	return (0);
}

/*
** Does the same as esc-r key sequence but only
** clears in the back and front
** Is used internally, for user there is esc-r
*/

int					clear_whole_line(void)
{
	while (g_rline.pos)
		key_left_proc();
	tputs(g_cap.cd, 1, printc);
	ft_bzero(g_rline.cmd, g_rline.cmd_buff_len);
	g_rline.cmd_len = 0;
	return (0);
}

int					save_questions_structure(t_rline_questions new_qw)
{
	front_for_questions.len = new_qw.len;
	front_for_questions.len_x = new_qw.len_x;
	front_for_questions.pos_back = new_qw.pos_back;
	return (0);
}

t_rline_questions	get_questions_structure(void)
{
	return (front_for_questions);
}