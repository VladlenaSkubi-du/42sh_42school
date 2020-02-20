/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_kwuae.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:21:19 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/20 19:14:17 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int			make_ctrl_k(void)
{
	char			*save_yank;

	check_menu();
	if (g_rline.pos == g_rline.cmd_len)
		return (incorrect_sequence());
	undo(0);
	save_yank = ft_strdup(g_rline.cmd + g_rline.pos);
	g_rline.cmd_len -= ft_strlen(g_rline.cmd + g_rline.pos);
	make_ctrl_y(0, save_yank);
	tputs(g_cap.cd, 1, printc);
	ft_bzero(g_rline.cmd + g_rline.pos, ft_strlen(g_rline.cmd + g_rline.pos));
	return (0);
}

int			make_ctrl_u(void)
{
	char			*swap;
	size_t			len_swap;
	char			*save_yank;

	check_menu();
	if (g_rline.pos == 0)
		return (incorrect_sequence());
	undo(0);
	save_yank = ft_strndup(g_rline.cmd, g_rline.pos);
	make_ctrl_y(0, save_yank);
	swap = g_rline.cmd + g_rline.pos;
	len_swap = ft_strlen(swap);
	front_set_cursor_jmp(&g_rline.pos,
		&g_rline.pos_x, &g_rline.pos_y, 1);
	while (g_rline.pos)
		key_left_proc();
	ft_strcpy(g_rline.cmd, swap);
	ft_bzero(g_rline.cmd + len_swap, g_rline.cmd_buff_len - len_swap);
	g_rline.cmd_len = 0 + len_swap;
	tputs(g_cap.cd, 1, printc);
	front_insert_cmd_till_the_end();
	return (0);
}

int			make_ctrl_a(void)
{
	size_t			pos_old;

	check_menu();
	pos_old = g_rline.pos;
	g_rline.pos = 0;
	move_cursor_from_old_position(pos_old, 'l');
	return (0);
}

int			make_ctrl_e(void)
{
	size_t			pos_old;

	check_menu();
	pos_old = g_rline.pos;
	g_rline.pos = g_rline.cmd_len;
	move_cursor_from_old_position(pos_old, 'r');
	return (0);
}

int			make_ctrl_w(void)
{
	size_t			pos_old;
	char			*swap;
	size_t			len_swap;
	char			*save_yank;

	check_menu();
	undo(0);
	pos_old = g_rline.pos;
	if (word_left_proc())
		return (0);
	front_set_cursor_jmp(&g_rline.pos,
		&g_rline.pos_x, &g_rline.pos_y, 1);
	save_yank = ft_strndup(g_rline.cmd + g_rline.pos, pos_old);
	make_ctrl_y(0, save_yank);
	swap = g_rline.cmd + pos_old;
	len_swap = ft_strlen(swap);
	g_rline.cmd_len = g_rline.pos + len_swap;
	ft_strcpy(g_rline.cmd + g_rline.pos, swap);
	ft_bzero(g_rline.cmd + g_rline.pos + len_swap,
		g_rline.cmd_buff_len - g_rline.cmd_len);
	tputs(g_cap.cd, 1, printc);
	front_insert_cmd_till_the_end();
	return (0);
}
