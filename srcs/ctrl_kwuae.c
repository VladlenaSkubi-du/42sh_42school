/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_kwuae.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:21:19 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/16 16:01:28 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int			make_ctrl_k(void)
{
	undo(0);
	putcap("cd");
	ft_bzero(g_rline.cmd + g_rline.pos, ft_strlen(g_rline.cmd + g_rline.pos));
	return (0);
}

int			make_ctrl_u(void)
{
	char			*swap;
	size_t			len_swap;
	
	undo(0);
	swap = g_rline.cmd + g_rline.pos;
	len_swap = ft_strlen(swap);
	ft_strcpy(g_rline.cmd, swap);
	ft_bzero(g_rline.cmd + len_swap, g_rline.cmd_buff_len - len_swap);
	while (g_rline.pos)
		key_left_proc();
	putcap("cd");
	ft_putstr_fd(g_rline.cmd, 1);
	if (move_cursor_back_after_print(0))
		return (-1);
	return (0);
}

int			make_ctrl_a(void)
{
	size_t			pos_old;

	pos_old = g_rline.pos;
	g_rline.pos = 0;
	if (move_cursor_from_old_position(pos_old, 'l'))
		return (-1);
	return (0);
}

int			make_ctrl_e(void)
{
	size_t			pos_old;

	pos_old = g_rline.pos;
	g_rline.pos = ft_strlen(g_rline.cmd) - 1;
	if (move_cursor_from_old_position(pos_old, 'r'))
		return (-1);
	return (0);
}

int			make_ctrl_w(void)
{
	size_t			pos_old;
	char			*swap;
	size_t			len_swap;

	undo(0);
	pos_old = g_rline.pos;
	if (word_left_proc())
		return (-1);
	swap = g_rline.cmd + pos_old;
	len_swap = ft_strlen(swap);
	ft_strcpy(g_rline.cmd + g_rline.pos, swap);
	ft_bzero(g_rline.cmd + g_rline.pos + len_swap,
		g_rline.cmd_buff_len - ft_strlen(g_rline.cmd));
	putcap("cd");
	ft_putstr_fd(g_rline.cmd + g_rline.pos, 1);
	if (move_cursor_back_after_print(0))
		return (-1);
	return (0);
}