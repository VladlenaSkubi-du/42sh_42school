/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esc_undo_completion_transpose.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:14:29 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/16 16:33:34 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int			undo_redraw(size_t pos_old)
{
	unsigned short	new_x;

	while (pos_old)
	{
		if (position_relative(&new_x, 0, pos_old))
			return (-1);
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
	if (move_cursor_back_after_print(0))
		return (-1);
	return (0);
}

int			esc_r(void)
{
	while (g_rline.pos)
		key_left_proc();
	putcap("cd");
	free(g_rline.cmd);
	init_readline();
	return (0);
}
