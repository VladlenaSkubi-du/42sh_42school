/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backend_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:56:28 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/07 20:51:37 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

int				find_assignment_in_variables(size_t var, size_t eq, size_t val)
{
	size_t		li;
	size_t		sy;
	char		*find;

	li = -1;
	sy = -1;
	find = ft_strndup(g_cmd + var, eq + 1);
	li = find_in_variables(g_env, &sy, find);
	if (li != -1)
		return (insert_assign_to_arrays(find, var, val, &g_env[li]));
	li = find_in_variables(g_shvar, &sy, find);
	if (li != -1)
	{
		insert_assign_to_arrays(find, var, val, &g_shvar[li]);
		check_if_histsize_changed();
		return (0);
	}
	li = find_in_variables(g_lovar, &sy, find);
	if (li != -1)
		return (insert_assign_to_arrays(find, var, val, &g_lovar[li]));
	free(find);
	find = ft_strndup(g_cmd + var, val);
	save_local_variables(find);
	return (0);
}

int				insert_assign_to_arrays(char *find, size_t var,
					size_t val, char **array)
{
	free(find);
	find = ft_strndup(g_cmd + var, val);
	free(*array);
	*array = find;
	return (0);
}
