/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_printable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 14:26:57 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/13 15:46:28 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int			backspace_process(void)
{
	if (g_rline.pos > 0)
	{
		ft_strcpy(g_rline.cmd + g_rline.pos - 1, g_rline.cmd + g_rline.pos);
		key_left_proc();
		putcap("cd");
		ft_putstr_fd(g_rline.cmd + g_rline.pos, 1);
		if (move_cursor_back_after_print())
			return (-1);
	}
	else
		return (incorrect_sequence());
	return (0);
}

int			delete_process(void)
{
	if (g_rline.pos < ft_strlen(g_rline.cmd))
	{
		ft_strcpy(g_rline.cmd + g_rline.pos, g_rline.cmd + g_rline.pos + 1);
		putcap("cd");
		ft_putstr_fd(g_rline.cmd + g_rline.pos, 1);
		if (move_cursor_back_after_print())
			return (-1);
	}
	else
		return (incorrect_sequence());
	return (0);
}
