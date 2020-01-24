/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 17:55:05 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/24 13:31:50 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int				make_sctrl_e(void)
{
	while (g_rline.pos < g_rline.cmd_len - 1 &&
		g_rline.pos + g_rline.prompt_len < g_screen.ws_col - 2)
		sesc_right();
	return (0);
}

int				make_sctrl_a(void)
{
	while (g_rline.pos)
		sesc_left();
	return (0);
}

int				sbackspace_proc(void)
{
	if (g_rline.pos == 0)
		return (bell_sound());
	g_rline.pos--;
	write(STDOUT_FILENO, "\033[D \033[D", 7);
	sstr_del_symbol();
	return (0);
}

int				make_sctrl_u(void)
{
	while (g_rline.pos)
		sbackspace_proc();
	return (0);
}

int				make_sctrl_k(void)
{
	size_t		pos_back;

	pos_back = g_rline.pos;
	while (g_rline.pos < g_rline.cmd_len - 1 &&
		g_rline.pos + g_rline.prompt_len < g_screen.ws_col - 2)
		sesc_right();
	while (g_rline.pos >= pos_back)
		sbackspace_proc();
	sesc_right();
	return (0);
}
