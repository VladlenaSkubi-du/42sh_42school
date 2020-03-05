/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back_part_hist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 13:15:19 by vladlenasku       #+#    #+#             */
/*   Updated: 2020/03/05 13:23:10 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int				find_in_history(char **find)
{
	int			i;
	char		*found;

	i = g_hist.last;
	while (i >= 0)
	{
		found = ft_strstr(g_hist.hist[i], *find);
		if (found != NULL)
		{
			free(*find);
			return (i);
		}
		i--;
	}
	free(*find);
	return (-1);
}

int				print_new_cmd_from_history(int coincidence)
{
	size_t		i;

	i = 0;
	esc_r();
	while (g_hist.hist[coincidence][i])
	{
		char_add(g_hist.hist[coincidence][i]);
		i++;
	}
	return (0);
}

int					delete_from_history()
{
	free(g_hist.hist[g_hist.last]);
	g_hist.hist[g_hist.last] = NULL;
	g_hist.last--;
	return (0);
}
