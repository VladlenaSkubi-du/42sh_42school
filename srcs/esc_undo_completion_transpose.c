/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esc_undo_completion_transpose.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshawand <hshawand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:14:29 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/13 16:50:44 by hshawand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int			undo_redraw(void)
{
	size_t	pos_save;

	pos_save = g_rline.pos;
	if (move_cursor_back_after_print())
			return (-1);
	while (g_rline.pos)
		key_left_proc();
	putcap("cd");
	g_rline.pos = pos_save;
	ft_putstr_fd(g_rline.cmd, 1);
	if (move_cursor_back_after_print())
			return (-1);
	return (0);
}

int			esc_r(void)
{
	unsigned short	end_x;
	unsigned short	end_y;

	if (position_relative(&end_x, &end_y, ft_strlen(g_rline.cmd)))
		return (-1);
	position_cursor("ch", 0, g_rline.prompt_len);
	if (end_y > 1)
		position_cursor("UP", 0, end_y - 1);
	putcap("cd");
	free(g_rline.cmd);
	init_readline();
	return (0);
}
