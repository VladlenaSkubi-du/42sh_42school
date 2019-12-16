/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_tl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 19:38:44 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/16 20:11:55 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int			make_ctrl_t(void)
{
	size_t			len;
	size_t			pos_old;

	undo(0);
	len = ft_strlen(g_rline.cmd);
	if (len == 1)
		return (incorrect_sequence());
	if (g_rline.pos == 0 || g_rline.pos == len)
	{
		if (make_ctrl_t_begend(len))
			return (-1);
	}
	else
	{
		swap_chars(g_rline.cmd, g_rline.pos, g_rline.pos - 1);
		pos_old = g_rline.pos;
		g_rline.pos--;
		if (move_cursor_from_old_position(pos_old, 'l'))
			return (-1);
		putcap("cd");
		ft_putstr_fd(g_rline.cmd + g_rline.pos, 1);
		g_rline.pos = pos_old + 1;
		if (move_cursor_back_after_print(0))
			return (-1);
	}
	return (0);
}

int			make_ctrl_t_begend(size_t len)
{
	size_t			pos_old;

	if (g_rline.pos == 0)
	{
		swap_chars(g_rline.cmd, g_rline.pos + 1, g_rline.pos);
		putcap("cd");
		ft_putstr_fd(g_rline.cmd, 1);
		g_rline.pos += 2;
		if (move_cursor_back_after_print(0))
			return (-1);
	}
	else if (g_rline.pos == len)
	{
		swap_chars(g_rline.cmd, g_rline.pos - 1, g_rline.pos - 2);
		pos_old = g_rline.pos;
		g_rline.pos -= 2;
		if (move_cursor_from_old_position(pos_old, 'l'))
			return (-1);
		putcap("cd");
		ft_putstr_fd(g_rline.cmd + g_rline.pos, 1);
		g_rline.pos = pos_old;
		if (move_cursor_back_after_print(0))
			return (-1);
	}
	return (0);
}

int			make_ctrl_l(void)
{
	return (0);
}
