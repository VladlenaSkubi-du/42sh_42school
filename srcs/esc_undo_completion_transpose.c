/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esc_undo_completion_transpose.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:14:29 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/13 16:59:23 by sschmele         ###   ########.fr       */
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
	while (g_rline.pos)
		key_left_proc();
	putcap("cd");
	free(g_rline.cmd);
	init_readline();
	return (0);
}
