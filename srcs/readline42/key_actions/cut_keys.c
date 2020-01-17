/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 14:26:57 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/17 14:23:41 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int			backspace_process(void)
{
	char		*swap;
	size_t		len_swap;

	check_menu();
	if (g_rline.pos > 0)
	{
		undo(0);
		swap = g_rline.cmd + g_rline.pos;
		len_swap = ft_strlen(swap);
		ft_strcpy(g_rline.cmd + g_rline.pos - 1, swap);
		ft_bzero(g_rline.cmd + g_rline.pos - 1 + len_swap,
			g_rline.cmd_buff_len - g_rline.cmd_len);
		key_left_proc();
		putcap("cd");
		ft_putstr_fd(g_rline.cmd + g_rline.pos, 1);
		move_cursor_back_after_print(1);
		g_rline.cmd_len--;
	}
	else
		return (incorrect_sequence());
	return (0);
}

int			delete_process(void)
{
	char		*swap;
	size_t		len_swap;

	check_menu();
	if (g_rline.pos == 0 && g_rline.cmd_len == 0)
		btin_exit(SUCCESS);
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
		move_cursor_back_after_print(0);
		g_rline.cmd_len--;
	}
	else
		return (incorrect_sequence());
	return (0);
}

int			esc_r(void)
{
	while (g_rline.pos)
		key_left_proc();
	putcap("cd");
	free(g_rline.cmd);
	init_readline();
	return (0);
}
