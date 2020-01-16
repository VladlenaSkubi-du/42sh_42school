/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_printable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 14:26:57 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/16 15:50:33 by sschmele         ###   ########.fr       */
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
			g_rline.cmd_buff_len - ft_strlen(g_rline.cmd));
		key_left_proc();
		putcap("cd");
		ft_putstr_fd(g_rline.cmd + g_rline.pos, 1);
		move_cursor_back_after_print(1);
	}
	else
		return (incorrect_sequence());
	return (0);
}

int			delete_process(void)
{
	char		*swap;
	size_t		len;
	size_t		len_swap;

	check_menu();
	len = ft_strlen(g_rline.cmd);
	if (g_rline.pos == 0 && len == 0)
		btin_exit(SUCCESS);
	if (g_rline.pos < len)
	{
		undo(0);
		swap = g_rline.cmd + g_rline.pos + 1;
		len_swap = ft_strlen(swap);
		ft_strcpy(g_rline.cmd + g_rline.pos, swap);
		ft_bzero(g_rline.cmd + g_rline.pos + len_swap,
			g_rline.cmd_buff_len - ft_strlen(g_rline.cmd));
		putcap("cd");
		ft_putstr_fd(g_rline.cmd + g_rline.pos, 1);
		move_cursor_back_after_print(0);
	}
	else
		return (incorrect_sequence());
	return (0);
}
