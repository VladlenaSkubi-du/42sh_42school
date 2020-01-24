/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_block.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 15:36:08 by rbednar           #+#    #+#             */
/*   Updated: 2020/01/24 13:31:50 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

/*
** This func needs to fill path in the struct of file
*/

char			*ft_take_path(char *dir_name)
{
	char	*new;

	if (dir_name[0] == '/' && dir_name[1] == '\0')
		new = ft_strdup(dir_name);
	else
	{
		new = ft_strnew(ft_strlen(dir_name) + 1);
		new = ft_strcpy(new, dir_name);
		new = ft_strcat(new, "/");
	}
	return (new);
}

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
