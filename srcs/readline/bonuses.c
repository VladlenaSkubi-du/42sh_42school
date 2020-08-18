/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonuses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 18:52:56 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/01 17:51:39 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

#define COLOR_NUM	6

char				*colors_process(int sequence_num)
{
	char			*seq_action[COLOR_NUM];

	seq_action[0] = RED;
	seq_action[1] = ORANGE;
	seq_action[2] = YELLOW;
	seq_action[3] = GREEN;
	seq_action[4] = BLUE;
	seq_action[5] = PURPLE;
	return (seq_action[sequence_num]);
}

int					kirill_lgbt(void)
{
	int				i;
	char			*color;
	char			*kirill;

	kirill = ft_strstr(g_rline.cmd, "kirill");
	if (kirill != NULL && g_rline.pos > 5 &&
		g_rline.cmd[g_rline.pos - 1] == 'l' &&
		g_rline.cmd[g_rline.pos - 2] == 'l')
	{
		i = -1;
		while (++i < 6)
			backspace_process();
		kirill = "kirill";
		i = -1;
		while (++i < 6)
		{
			color = colors_process(i);
			char_add(kirill[i], color);
		}
	}
	return (0);
}