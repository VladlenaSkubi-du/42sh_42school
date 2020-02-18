/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_processing42.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 13:27:42 by vladlenasku       #+#    #+#             */
/*   Updated: 2020/02/18 13:53:57 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

int					realloc_all_variables_array(void)
{
	ft_realloc_array(&g_env, g_var_size, g_var_size * 2);
	ft_realloc_array(&g_lovar, g_var_size, g_var_size * 2);
	g_var_size *= 2;
	return (0);
}

int					add_new_to_variables_array(char ***array, int size, char *add)
{
	size_t			i;
	char			**tmp;

	i = 0;
	tmp = *array;
	while (tmp[i])
		i++;
	
	return (0);
}