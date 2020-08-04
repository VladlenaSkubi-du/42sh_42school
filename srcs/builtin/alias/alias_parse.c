/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 15:08:22 by rbednar           #+#    #+#             */
/*   Updated: 2020/08/04 17:47:52 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

/*
** In the shell command language, a word consisting solely of underscores, 
** digits, and alphabetics from the portable character set and any of the
** following characters: '!', '%', ',', '@'.
*/

int		find_in_alias(char **arr, int *j, char *name)
{
	size_t	i;
	size_t	tmp;
	size_t	len_name;

	i = 0;
	if (!arr)
		return (-1);
	len_name = ft_strlen(name);
	while (arr[i])
	{
		tmp = ft_strchri(arr[i], '=');
		if (ft_strncmp(arr[i], name, len_name) == 0 && tmp == len_name)
		{
			*j = tmp + 1;
			return (i);
		}
		i++;
	}
	return (-1);
}

int		btin_alias_save(char **alias, char *arg)
{
	return (0);
}

int		btin_alias_print_one(char *arg)
{
	return (0);
}

int		btin_alias_merge_buf(char **arr, char **buf)
{
	return (0);
}
