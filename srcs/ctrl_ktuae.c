/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_ktuae.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:21:19 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/13 17:29:41 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int			make_ctrl_k(void)
{
	putcap("ce");
	ft_bzero(g_rline.cmd + g_rline.pos, ft_strlen(g_rline.cmd + g_rline.pos));
	return (0);
}

int			make_ctrl_t(void)
{
	size_t			len;

	len = ft_strlen(g_rline.cmd);
	if (len == 1)
	{
		putcap("bl");
		return (0);
	}
	if (g_rline.pos == 0)
		swap_chars(g_rline.cmd, g_rline.pos + 1, g_rline.pos);
	else if (g_rline.pos == len)
		swap_chars(g_rline.cmd, g_rline.pos - 1, g_rline.pos - 2);
	else
		swap_chars(g_rline.cmd, g_rline.pos, g_rline.pos - 1);
	cursor_till_word_begginning();
	//till the end - will be done
	return (0);
}

int			make_ctrl_u(void)
{
	ft_strcpy(g_rline.cmd, g_rline.cmd + g_rline.pos);
	while (g_rline.pos)
		key_left_proc();
	putcap("cd");
	ft_putstr_fd(g_rline.cmd, 1);
	if (move_cursor_back_after_print())
		return (-1);
	return (0);
}

int			make_ctrl_a(void)
{
	g_rline.pos = 0;
	if (move_cursor_back_after_print())
		return (-1);
	return (0);
}

int			make_ctrl_e(void)
{
	g_rline.pos = ft_strlen(g_rline.cmd) - 1;
	if (move_cursor_back_after_print())
		return (-1);
	return (0);
}