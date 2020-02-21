/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_edit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 14:16:46 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/21 19:29:36 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int					str_shift(char *str, int shift)
{
	char			*buff;

	buff = (char *)ft_xmalloc(ft_strlen(str) + 1);
	ft_strcpy(buff, str);
	ft_strcpy(str + shift, buff);
	free(buff);
	return (0);
}

int					char_add(char c)
{
	if (g_rline.cmd_len >= g_rline.cmd_buff_len - 1)
	{
		g_rline.cmd = (char *)ft_realloc(g_rline.cmd, g_rline.cmd_len,
			g_rline.cmd_buff_len,
			g_rline.cmd_buff_len + CMD_SIZE);
		g_rline.cmd_buff_len += CMD_SIZE;
	}
	undo(0);
	g_rline.cmd_len++;
	insert_char(c);
	return (0);
}

/*
** putcap("cd") - clearing till the end of the screen
** putcap("sf") - if cmd-line finishes of the most right position in terminal,
** the cursor should jump to the next line
*/

int					insert_char(char c)
{
	if (g_rline.cmd[g_rline.pos] != '\0')
	{
		str_shift(g_rline.cmd + g_rline.pos, 1);
		g_rline.cmd[g_rline.pos] = c;
		tputs(g_cap.cd, 1, printc);
		front_insert_one_char(g_rline.cmd[g_rline.pos]);
		g_rline.pos++;
		front_set_cursor_jmp(&g_rline.pos, &g_rline.pos_x, &g_rline.pos_y, 1);
		front_insert_cmd_till_the_end();
	}
	else
	{
		g_rline.cmd[g_rline.pos] = c;
		g_rline.pos++;
		front_insert_one_char(c);
	}
	return (0);
}

int					insert_line_till_the_end(size_t beg, size_t end)
{
	// size_t			i;
	// int				new_x;
	// int				end_y;
	// char			c;

	// i = beg;
	// while (i < end)
	// {
	// 	c = g_rline.cmd[i];
	// 	write(STDOUT_FILENO, &c, 1);
	// 	position_relative(&new_x, 0, i);
	// 	if (new_x == g_screen.ws_col - 1 && c != '\n')
	// 		putcap("sf");
	// 	i++;
	// }
	// position_relative(0, &end_y, g_rline.cmd_len - 1);
	// g_rline.str_num = end_y;
	// return (0);
}
