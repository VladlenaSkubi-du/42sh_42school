/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 14:26:57 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/14 18:26:28 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int					backspace_process(void)
{
	char			*swap;
	size_t			len_swap;

	check_menu();
	if (g_rline.pos > 0)
	{
		undo(0);
		swap = g_rline.cmd + g_rline.pos;
		len_swap = ft_strlen(swap);
		if (g_rline.cmd[g_rline.pos - 1] == '\n')
			return (backspace_newline(swap, len_swap));
		ft_strcpy(g_rline.cmd + g_rline.pos - 1, swap);
		ft_bzero(g_rline.cmd + g_rline.pos - 1 + len_swap,
			g_rline.cmd_buff_len - g_rline.cmd_len);
		key_left_proc();
		putcap("cd");
		insert_line_till_the_end(g_rline.pos, g_rline.cmd_len - 1);
		g_rline.cmd_len--;
		move_cursor_back_after_print(1);
	}
	else
		return (incorrect_sequence());
	return (0);
}

int					backspace_newline(char *swap, size_t len_swap)
{
	unsigned short	new_x;
	unsigned short	new_y;
	size_t			pos_back;

	pos_back = g_rline.pos;
	key_left_proc();
	position_relative(&new_x, &new_y, g_rline.pos);
	ft_strcpy(g_rline.cmd + pos_back - 1, swap);
	ft_bzero(g_rline.cmd + pos_back - 1 + len_swap,
		g_rline.cmd_buff_len - g_rline.cmd_len);
	putcap("cd");
	insert_line_till_the_end(g_rline.pos, g_rline.cmd_len - 1);
	g_rline.cmd_len--;
	if (g_rline.pos == g_rline.cmd_len)
		return (0);
	position_cursor("ch", 0, new_x);
	if (g_rline.str_num - new_y == 1 && new_y != 1)
		putcap("up");
	else if (g_rline.str_num - new_y > 1)
		position_cursor("UP", 0, g_rline.str_num - new_y);
	return (0);
}

int					delete_process(void)
{
	char			*swap;
	size_t			len_swap;

	check_menu();
	if (g_rline.pos == 0 && g_rline.cmd_len == 0)
		if (route_exit() == OUT)
			return (OUT);
	if (g_rline.pos < g_rline.cmd_len)
	{
		undo(0);
		swap = g_rline.cmd + g_rline.pos + 1;
		len_swap = ft_strlen(swap);
		ft_strcpy(g_rline.cmd + g_rline.pos, swap);
		ft_bzero(g_rline.cmd + g_rline.pos + len_swap,
			g_rline.cmd_buff_len - g_rline.cmd_len);
		putcap("cd");
		ft_putstr_fd(g_rline.cmd + g_rline.pos, 1);
		recount_str_num(g_rline.cmd_len - 1);
		g_rline.cmd_len--;
		move_cursor_back_after_print(1);
	}
	else
		return (incorrect_sequence());
	return (0);
}

int					route_exit(void)
{
	if (g_prompt.prompt_func == main_prompt)
	{
		action_alloc_management(NULL, 1);
		reset_canonical_input();
		clean_readline42();
		btin_exit(SUCCESS);
	}
	if (g_prompt.prompt_func != main_prompt)
	{
		g_rline.cmd = ft_straddsy(g_rline.cmd, EOF);
		return (OUT);
	}
	return (0);
}

int					esc_r(void)
{
	while (g_rline.pos)
		key_left_proc();
	putcap("cd");
	free(g_rline.cmd);
	init_readline();
	return (0);
}
