/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 17:55:26 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/06 20:38:45 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

/*
** Problems here: 
** 1) prompt exists only in the first line
** 2) if there are several lines and we stay on the most right position and push
** "move right" - we need to position in the beginning of the next line;
** if we are on the most left position and push "move left" - we need to 
** position in the end of the previous line - so we always need to count on
** what line we are standing on
** 3) position is counted starting from zero - sometimes there is minus 1 when
** we compare with the number of columns
**
** by 'while (g_rline.pos + g_rline.prompt_len > (sz.ws_col - 1) * i)' we get
** the line the cursor (== position) is on
*/

int		key_right_proc(void)
{
	struct winsize	sz;
	unsigned int	i;

	ioctl(1, TIOCGWINSZ, &sz);
	i = 1;
	if (g_rline.pos >= ft_strlen(g_rline.cmd))
	{
		putcap("bl");
		return (0);
	}
	if (g_rline.str_num > 1)
	{
		while (g_rline.pos + g_rline.prompt_len >= sz.ws_col * i)
			i++;
	}
	if (g_rline.pos + g_rline.prompt_len < sz.ws_col * i - 1)
		putcap("nd");
	else if (g_rline.pos + g_rline.prompt_len ==
				sz.ws_col * i - 1)
	{
		putcap("cr");
		putcap("do");
	}
	g_rline.pos++;
	return (0);
}

int		key_left_proc(void)
{
	struct winsize	sz;

	ioctl(1, TIOCGWINSZ, &sz);
	if (g_rline.pos == 0)
	{
		putcap("bl");
		return (0);
	}
	if (g_rline.pos > 0)
		putcap("le");
	else if ((g_rline.pos + g_rline.prompt_len) % (sz.ws_col + 1) == 0)
	{
		putcap("up");
		position_cursor("ch", 0, sz.ws_col);
	}
	g_rline.pos--;
	return (0);
}

int		key_up_proc(void)
{
	// ft_putendl("Pressed up");
	return (0);
}

int		key_down_proc(void)
{
//	ft_putendl("Pressed down");
	return (0);
}
