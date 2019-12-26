/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_tly.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 19:38:44 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/26 13:55:55 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int			make_ctrl_l(void) //проскролить в самый вверх
{
	size_t			pos_back;
	
	pos_back = g_rline.pos;
	g_rline.pos = 0;
	move_cursor_from_old_position(pos_back, 'l');
	position_cursor("ch", 0, 0);
	putcap("cd");
	putcap("cl");
	g_rline.pos = pos_back;
	main_promt(); //исправить
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

int			make_ctrl_y(int mode, char *yank)
{
	static char		*yank_str;
	static size_t	len_yank;

	if (mode == 0)
	{
		(yank_str) ? free(yank_str) : 0;
		if (yank)
		{
			yank_str = yank;
			len_yank = ft_strlen(yank_str);
		}
	}
	else if (mode == 1)
	{
		if (yank_str == NULL)
			return (incorrect_sequence());
		yank_insert(yank_str, len_yank);
	}
	else
		free(yank_str);
	return (0);
}

int			yank_insert(char *yank_str, size_t len_yank)
{
	char			*save;
	size_t			i;

	if (g_rline.cmd[g_rline.pos])
	{
		save = ft_strdup(g_rline.cmd + g_rline.pos);
		ft_bzero(g_rline.cmd + g_rline.pos, g_rline.cmd_buff_len - g_rline.pos);
	}
	else
		save = NULL;
	putcap("cd");
	i = -1;
	while (yank_str[++i])
		char_add(yank_str[i]);
	if (save)
		ft_strcpy(g_rline.cmd + g_rline.pos, save);
	ft_putstr_fd(g_rline.cmd + g_rline.pos, 1);
	move_cursor_back_after_print(1);
	free(save);
	return (0);
}
