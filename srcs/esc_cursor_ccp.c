/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esc_cursor_ccp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:34:11 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/14 18:41:06 by sschmele         ###   ########.fr       */
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
