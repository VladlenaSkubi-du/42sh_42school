/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 18:43:04 by rbednar           #+#    #+#             */
/*   Updated: 2020/03/12 21:15:09 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

static int	unset_from_array(char **arr, t_ltree *pos, int i)
{
	if (i == 0)
	{
		free(arr[i]);
		arr[0] = NULL;
		return (0);
	}
	free(arr[i]);
	arr[i] = arr[i + 1];
	i++;
	while (arr[i])
	{
		arr[i] = arr[i + 1];
	}
	return (0);
}

int			btin_unset(t_ltree *pos)
{
	size_t	unused;
	int		j;
	size_t	i;

	i = 1;
	while (i < pos->ar_c)
	{
		if ((j = find_in_variables(g_env, &unused, pos->ar_v[i])) != -1)
			unset_from_array(g_env, pos, j);
		if ((j = find_in_variables(g_lovar, &unused, pos->ar_v[i])) != -1)	
			unset_from_array(g_lovar, pos, j);
		i++;
	}
	return (0);	
}