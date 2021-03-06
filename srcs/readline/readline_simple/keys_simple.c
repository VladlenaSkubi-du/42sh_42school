/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 18:50:27 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/25 18:50:28 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int				make_sctrl_e(void)
{
	while (g_rline.pos < g_rline.cmd_len - 1 &&
			g_rline.pos + g_prompt.prompt_len < g_screen.ws_col - 2)
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
	g_rline.cmd_len--;
	return (0);
}
