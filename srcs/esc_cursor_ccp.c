/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esc_cursor_ccp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:34:11 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/13 17:42:55 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int			word_left_proc(void)
{
	size_t			i;

	i = g_rline.pos;
	while (g_rline.cmd[i] != ' ' && i != 0)
		i--;
	g_rline.pos = i + 1;
	if (move_cursor_back_after_print())
		return (-1);
	return (0);
}

int			word_right_proc(void)
{
	return (0);
}
