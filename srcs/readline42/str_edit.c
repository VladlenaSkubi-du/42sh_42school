/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_edit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 14:16:46 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/16 19:58:27 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	static size_t	sz_max = CMD_SIZE + 1;
	static size_t	sz = 0;

	if (sz >= sz_max - 1)
	{
		g_rline.cmd = (char *)ft_realloc(g_rline.cmd, sz, sz_max,
			sz_max + CMD_SIZE);
		sz_max += CMD_SIZE;
	}
	sz++;
	g_rline.cmd_buff_len = sz_max;
	undo(0);
	insert_char(c);
	return (0);
}

/*
** putcap("cd") - clearing till the end of the screen
** putcap("sf") - if cmd-line finishes of the most right position in terminal,
** the cursor should jump to the next line
*/

int				insert_char(char c)
{
	if (g_rline.cmd[g_rline.pos] != '\0')
	{
		str_shift(g_rline.cmd + g_rline.pos, 1);
		g_rline.cmd[g_rline.pos] = c;
		putcap("cd");
		ft_putstr_fd(g_rline.cmd + g_rline.pos, 1);
		g_rline.pos++;
		move_cursor_back_after_print(0);
	}
	else
	{
		write(STDOUT_FILENO, &c, 1);
		g_rline.cmd[g_rline.pos] = c;
		g_rline.str_num = count_str_num();
		if (g_rline.pos + g_rline.prompt_len + 1 ==
			g_screen.ws_col * g_rline.str_num)
			putcap("sf");
		g_rline.pos++;
	}
	return (0);
}

int				count_str_num(void)
	//put it also if we catch the signal SIGWINCH
{
	unsigned int	i;
	size_t			len;

	i = 1;
	len = ft_strlen(g_rline.cmd);
	if (len + g_rline.prompt_len > g_screen.ws_col)
	{
		while (len + g_rline.prompt_len >
			g_screen.ws_col * i)
			i++;
	}
	return (i);
}
