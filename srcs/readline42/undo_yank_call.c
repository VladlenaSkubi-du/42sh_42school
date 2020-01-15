/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undo_yank_call.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:41:23 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/04 15:21:16 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int			make_ctrl_x(void)
{
	char			next;

	check_menu();
	read(1, &next, 1);
	if (next == '\025')
		undo(1);
	else
		incorrect_sequence();
	return (0);
}

int			undo_wrap(void)
{
	return (undo(1));
}

int			undo_redraw(size_t pos_old)
{
	unsigned short	new_x;

	while (pos_old)
	{
		position_relative(&new_x, 0, pos_old);
		if (pos_old == 0)
			return (incorrect_sequence());
		if (new_x > 0)
			putcap("le");
		else if (new_x == 0)
		{
			position_cursor("ch", 0, g_screen.ws_col - 1);
			putcap("up");
		}
		pos_old--;
	}
	putcap("cd");
	ft_putstr_fd(g_rline.cmd, 1);
	move_cursor_back_after_print(0);
	return (0);
}

int			make_ctrl_y_wrap(void)
{
	return (make_ctrl_y(1, NULL));
}
