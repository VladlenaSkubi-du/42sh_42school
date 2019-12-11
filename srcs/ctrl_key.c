/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 19:03:25 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/11 17:05:35 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

/*
** Ctrl: Ctrl-k, ctrl-t, ctrl-u (ctrl-w) is here (I take)
*/

int			make_ctrl_x(void)
{
	char	next;

	read(1, &next, 1);
	if (next == '\025')
		undo(1);
	else
		incorrect_sequence();
	return (0);
}

int			ctrl_key(char sy)
{
	if (sy == '\013')
		make_ctrl_k();
	else if (sy == '\024')
		make_ctrl_t();
	else if (sy == '\025')
		make_ctrl_u();
	else if (sy == '\027')
		write(STDERR_FILENO, "Ctrl-W\n", 11);
	else if (sy == 127 || sy == '\010')
		backspace_process();
	else if (sy == 24)
		make_ctrl_x();
	return (0);
}

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
	while (g_rline.pos)
		key_left_proc();
	putcap("cd");
	free(g_rline.cmd);
	init_readline();
	return (0);
}