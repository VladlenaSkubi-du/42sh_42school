/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_block.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 15:36:08 by rbednar           #+#    #+#             */
/*   Updated: 2020/01/20 13:47:35 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

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
** Added path info to file.
*/

void			ft_addpath(char *name, t_path **buf)
{
	char		*dir_path;

	dir_path = ft_take_path(name);
	(*buf)->path = ft_strnew(ft_strlen(name) \
	+ ft_strlen((*buf)->name) + 1);
	(*buf)->path = ft_strcpy((*buf)->path, dir_path);
	(*buf)->path = ft_strcat((*buf)->path, (*buf)->name);
	free(dir_path);
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
