/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backend_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:56:28 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/04 14:01:01 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

int				find_assignment_in_variables(t_ltree *sub, size_t var,
				size_t eq, size_t val)
{
	size_t		li;
	size_t		sy;
	char		*find;

	li = -1;
	sy = -1;
	find = ft_strndup(sub->l_cmd + var, eq + 1);
	if (check_readonly_variables(find) == OUT)
		return (OUT); //выход из парсера в ридлайн
	if ((li = find_in_variables(g_env, &sy, find)) != -1)
		return (insert_assign_to_arrays(find, ft_strndup(sub->l_cmd + var, val),
			&g_env[li], sub));
	if ((li = find_in_variables(g_shvar, &sy, find)) != -1)
	{
		insert_assign_to_arrays(find, ft_strndup(sub->l_cmd + var, val), 
			&g_shvar[li], sub);
		return (check_if_histsize_changed());
	}
	if ((li = find_in_variables(g_lovar, &sy, find)) != -1)
		return (insert_assign_to_arrays(find, ft_strndup(sub->l_cmd + var, val),
			&g_lovar[li], sub));
	free(find);
	find = ft_strndup(sub->l_cmd + var, val);
	save_local_variables(find);
	return (0);
}

int				check_readonly_variables(char *find)
{
	size_t		li;
	size_t		sy;
	
	if ((li = find_in_variables(g_rdovar, &sy, find)) != -1)
	{
		error_handler(VARIABLE_ERROR, find);
		return (OUT);
	}
	return (0);
}

int				insert_assign_to_arrays(char *find, char *insert,
					char **array, t_ltree *sub)
{
	free(find);
	free(*array);
	*array = insert;
	return (0);
}
