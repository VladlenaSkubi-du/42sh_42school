/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_kult.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmp <tmp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 22:33:26 by tmp               #+#    #+#             */
/*   Updated: 2020/05/30 22:33:48 by tmp              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int			make_ctrl_k(void)
{
	char			*save_yank;

	check_after_line();
	if (g_rline.pos < 0 || g_rline.pos == g_rline.cmd_len)
		return (incorrect_sequence());
	undo(0);
	save_yank = ft_strdup(g_rline.cmd + g_rline.pos);
	g_rline.cmd_len -= ft_strlen(g_rline.cmd + g_rline.pos);
	make_ctrl_p(0, save_yank);
	tputs(g_cap.cd, 1, printc);
	ft_bzero(g_rline.cmd + g_rline.pos,
		ft_strlen(g_rline.cmd + g_rline.pos));
	return (0);
}

int			make_ctrl_u(void)
{
	int				pos_old;
	char			*swap;
	int				len_swap;
	char			*save_yank;

	check_after_line();
	if (g_rline.pos <= 0)
		return (incorrect_sequence());
	undo(0);
	pos_old = g_rline.pos;
	while (g_rline.pos)
		key_left_proc();
	front_set_cursor_jmp(&g_rline.pos, &g_rline.pos_x, &g_rline.pos_y, 1);
	save_yank = (pos_old == g_rline.cmd_len) ?
		ft_strdup(g_rline.cmd + g_rline.pos) :
		ft_strndup(g_rline.cmd + g_rline.pos, pos_old);
	make_ctrl_p(0, save_yank);
	swap = g_rline.cmd + pos_old;
	len_swap = ft_strlen(swap);
	ft_strcpy(g_rline.cmd, swap);
	ft_bzero(g_rline.cmd + len_swap, g_rline.cmd_buff_len - len_swap);
	g_rline.cmd_len = 0 + len_swap;
	tputs(g_cap.cd, 1, printc);
	front_insert_cmd_till_the_end(g_rline.pos_y + 1);
	return (0);
}

int			make_ctrl_l(void)
{
	check_after_line();
	front_set_cursor_jmp(&g_rline.pos,
		&g_rline.pos_x, &g_rline.pos_y, 1);
	putcap("cl");
	g_prompt.prompt_func();
	g_rline.pos = 0;
	g_rline.pos_x = count_prompt_len();
	g_rline.pos_y = 0;
	front_insert_cmd_till_the_end(g_rline.pos_y + 1);
	return (0);
}

int			make_ctrl_t(void)
{
	check_after_line();
	if (g_rline.cmd_len == 1 || g_rline.cmd_len < 0)
		return (incorrect_sequence());
	undo(0);
	if (g_rline.pos == 0 || g_rline.pos == g_rline.cmd_len)
		return (make_ctrl_t_begend(g_rline.cmd_len));
	else
	{
		swap_chars(g_rline.cmd, g_rline.pos, g_rline.pos - 1);
		if (front_move_one_char_left(g_rline.pos_x))
			return (incorrect_sequence());
		g_rline.pos--;
		front_set_cursor_jmp(&g_rline.pos, &g_rline.pos_x, &g_rline.pos_y, 1);
		tputs(g_cap.cd, 1, printc);
		front_insert_cmd_till_the_end(g_rline.pos_y + 1);
	}
	return (0);
}

int			make_ctrl_t_begend(int len)
{
	int				pos_old;

	if (g_rline.pos == 0)
	{
		swap_chars(g_rline.cmd, g_rline.pos + 1, g_rline.pos);
		front_set_cursor_jmp(&g_rline.pos, &g_rline.pos_x, &g_rline.pos_y, 1);
		tputs(g_cap.cd, 1, printc);
		front_insert_cmd_till_the_end(g_rline.pos_y + 1);
	}
	else if (g_rline.pos == len)
	{
		swap_chars(g_rline.cmd, g_rline.pos - 1, g_rline.pos - 2);
		pos_old = g_rline.pos - 2;
		move_cursor_from_old_position(pos_old, 'l');
		front_set_cursor_jmp(&g_rline.pos, &g_rline.pos_x, &g_rline.pos_y, 1);
		tputs(g_cap.cd, 1, printc);
		front_insert_cmd_till_the_end(g_rline.pos_y + 1);
	}
	return (0);
}
