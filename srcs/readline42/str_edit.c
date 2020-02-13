/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_edit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 14:16:46 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/13 19:58:46 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int				str_shift(char *str, int shift)
{
	char			*buff;

	buff = (char *)ft_xmalloc(ft_strlen(str) + 1);
	ft_strcpy(buff, str);
	ft_strcpy(str + shift, buff);
	free(buff);
	return (0);
}

int				char_add(char c)
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
	unsigned short	new_x;
	// size_t			i;
	unsigned short	end_y;
	
	if (g_rline.cmd[g_rline.pos] != '\0')
	{
		str_shift(g_rline.cmd + g_rline.pos, 1);
		g_rline.cmd[g_rline.pos] = c;
		putcap("cd");
		ft_putstr_fd(g_rline.cmd + g_rline.pos, 1);
		position_relative(0, &end_y, g_rline.cmd_len - 1);
		g_rline.str_num = end_y;
		recount_str_num(g_rline.cmd_len - 1);
		g_rline.pos++;
		move_cursor_back_after_print(0);
	}
	else
	{
		write(STDOUT_FILENO, &c, 1);
		g_rline.cmd[g_rline.pos] = c;
		position_relative(&new_x, 0, g_rline.pos);
		// if (g_rline.pos + g_rline.prompt_len + 1 ==
		// 	g_screen.ws_col * g_rline.str_num)
		if (new_x == g_screen.ws_col - 1)
			putcap("sf");
		count_str_num(c);
		g_rline.pos++;
	}
	return (0);
}

int					count_str_num(char c)
{
	size_t			num_back;
	
	num_back = g_rline.str_num;
	if (c == '\n')
		g_rline.str_num++;
	if (g_rline.cmd_len + g_rline.prompt_len ==
		(g_screen.ws_col + 1) * num_back - (num_back - 1))
		g_rline.str_num++;
	return (0);
}

int					recount_str_num(size_t limit)
{
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	g_rline.str_num = 1;
	while (i < limit)
	{
		if (g_rline.cmd[i] == '\n')
			g_rline.str_num++;
		if (i + g_rline.prompt_len ==
			g_screen.ws_col * g_rline.str_num)
			g_rline.str_num++;
		i++;
	}
	return (0);
}
