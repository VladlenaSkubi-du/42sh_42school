/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 17:55:26 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/05 14:08:53 by sschmele         ###   ########.fr       */
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
	int				i;
	int				len;

	check_menu();
	if (g_hist.counter <= 0)
	{
		g_hist.counter = 0;
		return (0);
	}
	if (g_hist.counter > g_hist.last)
		save_current_grline(1);
	if (g_rline.cmd[0] && g_hist.counter <= g_hist.last)
	{
		free(g_hist.hist[g_hist.counter]);
		g_hist.hist[g_hist.counter] = ft_strdup(g_rline.cmd);
	}
	(g_rline.cmd[0]) ? esc_r() : 0;
	g_hist.counter--;
	i = -1;
	len = ft_strlen(g_hist.hist[g_hist.counter]);
	if (len > 0 && g_hist.hist[g_hist.counter][len - 1] == '\n')
		len--;
	while (++i < len)
		char_add(g_hist.hist[g_hist.counter][i]);
	return (0);
}

int		save_current_grline(int flag)
{
	static char		*current;
	static size_t	len;
	int				i;

	if (flag == 1)
	{
		current = ft_strdup(g_rline.cmd);
		len = g_rline.cmd_len;
	}
	else if (flag == 0)
	{
		i = -1;
		while (++i < len)
			char_add(current[i]);
	}
	else if (flag == 2)
	{
		free(current);
		current = NULL;
		len = 0;
	}
	return (0);
}

int		key_down_proc(void)
{
	int				i;
	int				len;

	check_menu();
	if (g_rline.cmd[0] && g_hist.counter <= g_hist.last)
	{
		free(g_hist.hist[g_hist.counter]);
		g_hist.hist[g_hist.counter] = ft_strdup(g_rline.cmd);
	}
	(g_rline.cmd[0]) ? esc_r() : 0;
	if (g_hist.counter >= g_hist.last)
	{
		save_current_grline(0);
		save_current_grline(2);
		g_hist.counter = g_hist.last + 1;
		return (0);
	}
	g_hist.counter++;
	i = -1;
	len = ft_strlen(g_hist.hist[g_hist.counter]);
	if (len > 0 && g_hist.hist[g_hist.counter][len - 1] == '\n')
		len--;
	while (++i < len)
		char_add(g_hist.hist[g_hist.counter][i]);
	return (0);
}
