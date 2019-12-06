/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 19:03:25 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/06 20:53:21 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

/*
** Ctrl: Ctrl-k, ctrl-t, ctrl-u (ctrl-w) is here (I take)
*/

int			ctrl_key(char sy)
{
	if (sy == '\013')
		make_ctrl_k();
	else if (sy == '\024')
		make_ctrl_t();
	else if (sy == '\025' || sy == '\027')
		write(STDERR_FILENO, "Ctrl-U(W)\n", 11);
	else if (sy == 127)
		backspace_process();
	return (0);
}

int			make_ctrl_k(void)
{
	position_cursor("DC", 0, ft_strlen(g_rline.cmd + g_rline.pos));
	ft_bzero(g_rline.cmd + g_rline.pos, ft_strlen(g_rline.cmd + g_rline.pos));
	return (0);
}

int			make_ctrl_t(void)
{
	// int			first;
	// int			second;
	// size_t		len;
	
	// len = ft_strlen(g_rline.cmd);
	// if (len == 1)
	// {
	// 	putcap("bl");
	// 	return (0);
	// }
	// if (g_rline.pos == 0)
	// {
	// 	first = g_rline.pos + 1;
	// 	second = g_rline.pos;
	// }
	// else if (g_rline.pos == len)
	// {
	// 	first = g_rline.pos - 2;
	// 	second = g_rline.pos - 1;
	// }
	// else
	// {
	// 	first = g_rline.pos;
	// 	second = g_rline.pos - 1;
	// }
	// swap_chars(g_rline.cmd, first, second);
	// if (g_rline.pos == len)
	// 	sequence_process(2);
	// sequence_process(2);
	// ft_putchar_fd(g_rline.cmd[second], 1);
	// ft_putchar_fd(g_rline.cmd[first], 1);
	return (0);
}
