/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_block.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 20:23:34 by rbednar           #+#    #+#             */
/*   Updated: 2020/08/07 20:23:35 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

/*
** Func fills **list by element of tree t_path
*/

static void		ft_fill_in_order(t_path **root, char **list, \
				size_t *len, int *max)
{
	int	bu;

	bu = 0;
	if (root != NULL && *root != NULL)
	{
		ft_fill_in_order(&((*root)->prev), list, len, max);
		if ((*root)->name != NULL)
		{
			list[*len] = ft_strdup((*root)->name);
			bu = ft_strlen((*root)->name);
			bu > *max ? *max = bu : 0;
			(*len)++;
		}
		ft_fill_in_order(&((*root)->next), list, len, max);
	}
}

/*
** Func fills **list by element of tree t_path
*/

char			**ft_add_block(t_path **root, size_t len, int *max)
{
	char	**list;
	size_t	l;

	l = 0;
	list = (char**)malloc(sizeof(char*) * (len + 1));
	list[len] = NULL;
	ft_fill_in_order(root, list, &l, max);
	return (list);
}
