/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easter_egg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:42:02 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/10 18:06:01 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int				kirill_lgbt(char sy)
{
	int			i;
	char		*color;
	char		*kirill;

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
