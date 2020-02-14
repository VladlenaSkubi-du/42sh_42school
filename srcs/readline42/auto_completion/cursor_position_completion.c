/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_position_completion.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 16:51:01 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/14 18:28:12 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int					position_cursor_for_menu(size_t len)
{
	size_t			pos_old;
	unsigned short	end_x;

	pos_old = g_rline.pos;
	if (g_rline.pos == 0 && len == 0)
		putcap("sf");
	else
	{
		g_rline.pos = len;
		move_cursor_from_old_position(pos_old, 'r');
		position_relative(&end_x, 0, g_rline.pos);
		if (end_x < g_screen.ws_col)
			putcap("sf");
	}
	return (0);
}

int					position_cursor_after_menu_back(unsigned short len_x,
						int buf_lines, size_t pos_back, size_t len)
{
	size_t			i;

	i = -1;
	position_cursor("ch", 0, len_x);
	while (++i < buf_lines)
		putcap("sr");
	g_rline.pos = pos_back;
	move_cursor_from_old_position(len, 'l');
	return (0);
}

int					delete_till_compl(size_t len_compl, size_t delete)
{
	char			*swap;
	size_t			len_swap;
	int				i;

	if (g_rline.pos > 0)
	{
		swap = g_rline.cmd + g_rline.pos;
		len_swap = ft_strlen(swap);
		ft_strcpy(g_rline.cmd + g_rline.pos - delete, swap);
		ft_bzero(g_rline.cmd + g_rline.pos - delete + len_swap,
			g_rline.cmd_buff_len - ft_strlen(g_rline.cmd));
		i = -1;
		while (++i < delete)
			key_left_proc();
		putcap("cd");
		ft_putstr_fd(g_rline.cmd + g_rline.pos, 1);
		g_rline.cmd_len -= delete;
		move_cursor_back_after_print(1);
	}
	else
		return (incorrect_sequence());
	return (0);
}
