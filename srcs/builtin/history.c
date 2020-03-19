/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 20:18:03 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/14 20:31:09 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

int					btin_history(void)
{
	int				i;
	int				num;
	int				tmp;

	i = 0;
	num = g_hist.last_fc - g_hist.last;
	while (g_hist.hist[i] && i < g_hist.len)
	{
		tmp = ft_strlen(g_hist.hist[i]);
		if (tmp > 0 && g_hist.hist[i][tmp - 1] == '\n')
			tmp -= 1;
		ft_printf("%5d  %.*s\n", num, tmp, g_hist.hist[i]);
		num++;
		i++;
	}
	return (0);
}