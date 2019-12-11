/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 19:03:25 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/11 15:46:19 by sschmele         ###   ########.fr       */
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
	else if (sy == '\025')
		make_ctrl_u();
	else if (sy == '\027')
		write(STDERR_FILENO, "Ctrl-W\n", 11);
	else if (sy == 127 || sy == '\010')
		backspace_process();
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
	unsigned short	end_x;
	unsigned short	end_y;
	size_t			i;

	i = 0;
	if (position_relative(&end_x, &end_y, ft_strlen(g_rline.cmd)))
		return (-1);
	if (end_x < g_rline.prompt_len)
	{
		while (end_x++ < g_rline.prompt_len)
			putcap("nd");
	}
	else if (end_x > g_rline.prompt_len - 1)
	{
		while (end_x-- > g_rline.prompt_len)
			putcap("le");
	}

	// position_cursor("ch", 0, g_rline.prompt_len);

	if (end_y > 1)
	{
		while (i++ < end_y - 1)
			putcap("up");
	}

	// if (end_y > 1)
		// position_cursor("UP", 0, end_y - 1);
		
	putcap("cd");
	free(g_rline.cmd);
	init_readline();
	return (0);
}