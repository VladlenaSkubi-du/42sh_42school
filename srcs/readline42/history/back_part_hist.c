/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back_part_hist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 13:15:19 by vladlenasku       #+#    #+#             */
/*   Updated: 2020/02/18 13:16:36 by vladlenasku      ###   ########.fr       */
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