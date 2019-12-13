/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esc_undo_completion_transpose.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:14:29 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/13 16:03:29 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int			esc_r(void)
{
	unsigned short	end_x;
	unsigned short	end_y;

	if (position_relative(&end_x, &end_y, ft_strlen(g_rline.cmd)))
		return (-1);
	position_cursor("ch", 0, g_rline.prompt_len);
	if (end_y > 1)
		position_cursor("UP", 0, end_y - 1);
	putcap("cd");
	free(g_rline.cmd);
	init_readline();
	return (0);
}
