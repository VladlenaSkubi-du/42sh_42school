/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 17:55:26 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/10 14:44:43 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
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

int		key_right_proc		(void)
{
	unsigned int	i;

	i = 1;
	if (g_rline.pos >= g_rline.cmd_len)
		return (incorrect_sequence());
	if (g_rline.str_num > 1)
		i = on_which_line(g_rline.pos + g_rline.prompt_len, g_screen.ws_col);
	if (g_rline.pos + g_rline.prompt_len < g_screen.ws_col * i - 1)
		putcap("nd");
	else if (g_rline.pos + g_rline.prompt_len ==
				g_screen.ws_col * i - 1)
	{
		putcap("cr");
		putcap("do");
	}
	g_rline.pos++;
	return (0);
}

int		key_left_proc(void)
{
	unsigned short	new_x;

	position_relative(&new_x, 0, g_rline.pos);
	if (g_rline.pos == 0)
		return (incorrect_sequence());
	if (new_x > 0)
		putcap("le");
	else if (new_x == 0)
	{
		position_cursor("ch", 0, g_screen.ws_col - 1);
		putcap("up");
	}
	g_rline.pos--;
	return (0);
}

int		key_up_proc(void)
{
	// int			i;
	// int			len;
	
	check_menu();
	// if (g_hist.counter < 0)
	// {
	// 	g_hist.counter = 0;
	// 	return (incorrect_sequence());
	// }
	// g_hist.counter--;
	// clean_rline_cmd();
	// i = 0;
	// len = ft_strlen(g_hist.hist[g_hist.counter]);
	// if (g_hist.hist[g_hist.counter][len - 1] == '\n')
	// 	len--;
	// while (i < len)
	// {
	// 	char_add(g_hist.hist[g_hist.counter][i]);
	// 	i++;
	// }
	// printf("%zu\n", g_rline.str_num);
	return (0);
}

int		clean_rline_cmd(void)
{
	while (g_rline.pos)
		key_left_proc();
	putcap("cd");
	free(g_rline.cmd);
	init_readline();
	return (0);
}

int		key_down_proc(void)
{
	// int			i;
	// int			len;
	
	check_menu();
	// if (g_hist.counter == g_hist.last)
	// {
	// 	clean_rline_cmd();
	// 	return (incorrect_sequence());
	// }
	// g_hist.counter++;
	// clean_rline_cmd();
	// i = 0;
	// len = ft_strlen(g_hist.hist[g_hist.counter]);
	// if (g_hist.hist[g_hist.counter][len - 1] == '\n')
	// 	len--;
	// while (i < len)
	// {
	// 	char_add(g_hist.hist[g_hist.counter][i]);
	// 	i++;
	// }
	return (0);
}
