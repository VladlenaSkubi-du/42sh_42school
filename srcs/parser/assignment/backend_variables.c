/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backend_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:56:28 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/04 19:18:01 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

int             find_assignment_in_variables(size_t var, size_t eq, size_t val)
{
	size_t      li;
	size_t      sy;
	char        *find;
	
	li = -1;
	sy = -1;
	find = ft_strndup(g_cmd + var, eq);
	li = find_in_variables(g_env, &sy, find);
	if (li != -1)
	{
		free(find);
		find = ft_strndup(g_cmd + var, val);
		free(g_env[li]);
		g_env[li] = find;
		return (0);
	}
	li = find_in_variables(g_shvar, &sy, find);
	if (li != -1)
	{
		free(find);
		find = ft_strndup(g_cmd + var, val);
		free(g_shvar[li]);
		g_shvar[li] = find;
		return (0);
	}
	li = find_in_variables(g_lovar, &sy, find);
	if (li != -1)
	{
		free(find);
		find = ft_strndup(g_cmd + var, val);
		free(g_lovar[li]);
		g_lovar[li] = find;
		return (0);
	}
	free(find);
	find = ft_strndup(g_cmd + var, val);
	save_local_variables(find);
	return (0);
}