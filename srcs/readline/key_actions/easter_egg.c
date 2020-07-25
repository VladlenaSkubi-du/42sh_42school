/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easter_egg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 18:47:38 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/25 18:47:39 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int				kirill_lgbt(void)
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
