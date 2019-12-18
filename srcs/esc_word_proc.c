/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esc_word_proc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:34:11 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/18 17:44:55 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int			word_left_proc(void)
{
	size_t			i;
	size_t			pos_old;

	if (g_rline.pos == 1)
	{
		putcap("le");
		g_rline.pos = 0;
		return (0);
	}
	else if (g_rline.pos == 0)
		return (incorrect_sequence());
	i = g_rline.pos - 1;
	pos_old = g_rline.pos;
	while (g_rline.cmd[i] && g_rline.cmd[i - 1])
	{
		if (ft_isalnum(g_rline.cmd[i]) && !ft_isalnum(g_rline.cmd[i - 1]))
			break ;
		i--;
	}
	g_rline.pos = i;
	if (move_cursor_from_old_position(pos_old, 'l'))
		return (-1);
	return (0);
}

int			word_right_proc(void)
{
	size_t			i;
	size_t			pos_old;
	size_t			len;

	len = ft_strlen(g_rline.cmd);
	if (g_rline.pos == len)
		return (incorrect_sequence());
	else if (g_rline.pos == len - 1)
	{
		putcap("nd");
		g_rline.pos = len;
		return (0);
	}
	i = g_rline.pos + 1;
	pos_old = g_rline.pos;
	while (g_rline.cmd[i] && g_rline.cmd[i - 1])
	{
		if (!ft_isalnum(g_rline.cmd[i]) && ft_isalnum(g_rline.cmd[i - 1]))
			break ;
		i++;
	}
	g_rline.pos = i;
	if (move_cursor_from_old_position(pos_old, 'r'))
		return (-1);
	return (0);
}

int			esc_d(void)
{
	size_t			pos_old;
	size_t			pos_back;
	char			*swap;
	size_t			len_swap;

	pos_old = g_rline.pos;
	if (word_right_proc())
		return (0);
	undo(0);
	swap = g_rline.cmd + g_rline.pos;
	len_swap = ft_strlen(swap);
	ft_strcpy(g_rline.cmd + pos_old, swap);
	ft_bzero(g_rline.cmd + pos_old + len_swap,
		g_rline.cmd_buff_len - ft_strlen(g_rline.cmd));
	pos_back = g_rline.pos;
	g_rline.pos = pos_old;
	move_cursor_from_old_position(pos_back, 'l');
	putcap("cd");
	ft_putstr_fd(g_rline.cmd + g_rline.pos, 1);
	move_cursor_back_after_print(0);
	return (0);
}

int			esc_r(void) //maybe replace from this file
{
	while (g_rline.pos)
		key_left_proc();
	putcap("cd");
	free(g_rline.cmd);
	init_readline();
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
