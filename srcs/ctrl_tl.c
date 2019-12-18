/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_tl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 19:38:44 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/18 17:46:40 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int			make_ctrl_l(void)
{
	putcap("ti");
	main_promt();
	ft_putstr_fd(g_rline.cmd, 1);
	move_cursor_back_after_print(0);
	return (0);
}

int			make_ctrl_t(void)
{
	size_t			len;
	size_t			pos_old;

	len = ft_strlen(g_rline.cmd);
	if (len == 1)
		return (incorrect_sequence());
	undo(0);
	if (g_rline.pos == 0 || g_rline.pos == len)
		return (make_ctrl_t_begend(len));
	else
	{
		swap_chars(g_rline.cmd, g_rline.pos, g_rline.pos - 1);
		pos_old = g_rline.pos;
		g_rline.pos--;
		move_cursor_from_old_position(pos_old, 'l');
		putcap("cd");
		ft_putstr_fd(g_rline.cmd + g_rline.pos, 1);
		g_rline.pos = pos_old + 1;
		move_cursor_back_after_print(0);
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
		move_cursor_back_after_print(0);
	}
	else if (g_rline.pos == len)
	{
		swap_chars(g_rline.cmd, g_rline.pos - 1, g_rline.pos - 2);
		pos_old = g_rline.pos;
		g_rline.pos -= 2;
		move_cursor_from_old_position(pos_old, 'l');
		putcap("cd");
		ft_putstr_fd(g_rline.cmd + g_rline.pos, 1);
		g_rline.pos = pos_old;
		move_cursor_back_after_print(0);
	}
	return (0);
}
