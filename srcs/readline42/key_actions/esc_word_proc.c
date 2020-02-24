/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esc_word_proc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:34:11 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/24 19:16:34 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int			word_left_proc(void)
{
	size_t			i;
	size_t			pos_old;

	if (g_rline.pos == 1 || g_rline.pos == 2)
	{
		tputs(g_cap.le, 1, printc);
		(g_rline.pos == 2) ? tputs(g_cap.le, 1, printc) : 0;
		g_rline.pos = 0;
		return (0);
	}
	else if (g_rline.pos == 0)
		return (incorrect_sequence());
	i = g_rline.pos - 1;
	while (i > 0 && g_rline.cmd[i - 1] && g_rline.cmd[i])
	{
		if (ft_isalnum(g_rline.cmd[i]) && !ft_isalnum(g_rline.cmd[i - 1]))
			break ;
		i--;
	}
	pos_old = i;
	if (move_cursor_from_old_position(pos_old, 'l'))
		return (-1);
	return (0);
}

int			word_right_proc(void)
{
	size_t			i;
	size_t			pos_old;

	if (g_rline.pos == g_rline.cmd_len)
		return (incorrect_sequence());
	else if (g_rline.pos == g_rline.cmd_len - 1)
	{
		tputs(g_cap.nd, 1, printc);
		g_rline.pos = g_rline.cmd_len;
		return (0);
	}
	i = g_rline.pos + 1;
	while (g_rline.cmd[i] && g_rline.cmd[i - 1])
	{
		if (!ft_isalnum(g_rline.cmd[i]) && ft_isalnum(g_rline.cmd[i - 1]))
			break ;
		i++;
	}
	pos_old = i;
	if (move_cursor_from_old_position(pos_old, 'r'))
		return (-1);
	return (0);
}

int			esc_d(void)
{
	size_t			pos_old;
	char			*swap;
	size_t			len_swap;
	char			*save_yank;

	pos_old = g_rline.pos;
	if (word_right_proc())
		return (0);
	undo(0);
	save_yank = ft_strndup(g_rline.cmd + pos_old, g_rline.pos);
	make_ctrl_y(0, save_yank);
	swap = g_rline.cmd + g_rline.pos;
	len_swap = ft_strlen(swap);
	g_rline.cmd_len = pos_old + len_swap;
	ft_strcpy(g_rline.cmd + pos_old, swap);
	ft_bzero(g_rline.cmd + pos_old + len_swap,
		g_rline.cmd_buff_len - g_rline.cmd_len);
	move_cursor_from_old_position(pos_old, 'l');
	front_set_cursor_jmp(&g_rline.pos,
		&g_rline.pos_x, &g_rline.pos_y, 1);
	tputs(g_cap.cd, 1, printc);
	front_insert_cmd_till_the_end(g_rline.pos_y + 1);
	return (0);
}

char		*save_word(size_t *i, char *cmd, size_t pos)
{
	char			*word;

	word = NULL;
	*i = 0;
	while (ft_isalnum(cmd[pos + *i]))
		(*i)++;
	word = ft_strndup(cmd + pos, *i);
	return (word);
}

char		*save_end(size_t pos_back)
{
	char			*end;
	size_t			pos_now;

	end = NULL;
	pos_now = g_rline.pos;
	move_cursor_from_old_position(pos_back, 'r');
	if (word_right_proc())
		return (end);
	end = ft_strdup(g_rline.cmd + g_rline.pos);
	move_cursor_from_old_position(pos_now, 'l');
	return (end);
}
