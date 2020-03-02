/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 17:55:26 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/02 19:07:51 by rbednar          ###   ########.fr       */
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

int		key_right_proc(void)
{
	if (g_rline.pos >= g_rline.cmd_len)
		return (incorrect_sequence());
	front_move_one_char_right(g_rline.pos_x);
	g_rline.pos++;
	return (0);
}

int		key_left_proc(void)
{
	if (g_rline.pos == 0)
		return (incorrect_sequence());
	front_move_one_char_left(g_rline.pos_x);
	g_rline.pos--;
	return (0);
}

int		key_up_proc(void)
{
	int			i;
	int			len;

	check_menu();
	if (g_hist.counter <= 0)
	{
		g_hist.counter = 0;
		return (incorrect_sequence());
	}
	free(g_hist.hist[g_hist.counter]);
	g_hist.hist[g_hist.counter] = ft_strdup(g_rline.cmd);
	g_hist.counter--;
	clean_rline_cmd();
	i = 0;
	len = ft_strlen(g_hist.hist[g_hist.counter]);
	if (g_hist.hist[g_hist.counter][len - 1] == '\n')
		len--;
	while (i < len)
	{
		char_add(g_hist.hist[g_hist.counter][i]);
		i++;
	}
	return (0);
}

int		clean_rline_cmd(void)
{
	while (g_rline.pos)
		key_left_proc();
	tputs(g_cap.cd, 1, printc);
	free(g_rline.cmd);
	init_readline();
	return (0);
}

int		key_down_proc(void)
{
	int			i;
	int			len;

	check_menu();
	if (g_hist.counter >= g_hist.last)
	{
		g_hist.counter = g_hist.last + 1;
		clean_rline_cmd();
		return (incorrect_sequence());
	}
	free(g_hist.hist[g_hist.counter]);
	g_hist.hist[g_hist.counter] = ft_strdup(g_rline.cmd);
	g_hist.counter++;
	clean_rline_cmd();
	i = 0;
	len = ft_strlen(g_hist.hist[g_hist.counter]);
	if (g_hist.hist[g_hist.counter][len - 1] == '\n')
		len--;
	while (i < len)
	{
		char_add(g_hist.hist[g_hist.counter][i]);
		i++;
	}
	return (0);
}
