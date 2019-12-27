/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 15:36:08 by rbednar           #+#    #+#             */
/*   Updated: 2019/12/27 14:04:49 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

/*
** Func init t_path element
*/

static t_path	*ft_init_path(char *name, t_dirent *dp)
{
	t_path	*temp;

	if ((temp = (t_path*)malloc(sizeof(t_path))))
	{
		temp->name = ft_strdup(dp->d_name);
		temp->path = dp->d_name;
		ft_addpath(name, temp);
		temp->prev = NULL;
		temp->next = NULL;
		return (temp);
	}
	else
		return (NULL);
}

/*
** Func insert t_path element by *root element if it exist
*/

static int		ft_insert_in(char *name, t_path **root, t_path **temp)
{
	t_path	*current;
	t_path	*parent;

	current = *root;
	while (1)
	{
		parent = current;
		if (!(ft_strcmp((*temp)->name, parent->name)))
			return (0);
		else if (ft_strcmp((*temp)->name, parent->name) < 0)
		{
			current = current->prev;
			if (current == NULL)
			{
				parent->prev = *temp;
				return (0);
			}
		}
		else
		{
			current = current->next;
			if (current == NULL)
			{
				parent->next = *temp;
				return (0);
			}
		}
	}
}

/*
** Func insert t_path element by *root element in all conditions
*/

static void		insert(char *name, t_dirent *dp, t_path **root, size_t *len)
{
	t_path	*temp;
	t_path	**current;

	temp = ft_init_path(name, dp);
	if (*root == NULL)
		*root = temp;
	else
	{
		if (!(ft_insert_in(name, root, &temp)))
			return ;
		else
		{
			free(temp);
			(*len)++;
		}
	}
}

/*
** Func finds files in dir and add it to tree of type t_path
*/

void			ft_get_path(char *name, t_path **root, size_t *len, char *find)
{
	DIR			*dir;
	t_stat		*stat_b;
	t_dirent	*dp;

	if ((stat_b = (t_stat *)malloc(sizeof(t_stat))) == NULL)
		return ;
	if (lstat(name, stat_b) == -1)
		return ;
	if (!(dir = opendir(name)))
		return ;
	while (dir != NULL)
	{
		if ((dp = readdir(dir)) != NULL)
		{
			if (ft_strnequ(dp->d_name, find, ft_strlen(find)))
				insert(name, dp, root, len);
		}
		else
			closedir(dir) == 0 ? dir = NULL : 0;
	}
	free(stat_b);
}

/*
** Func find and return **char of all insertions of string find in PATH
*/

char			**ft_path_pars(char *find, char *path)
{
	t_path	*root;
	char	**list;
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	root = NULL;
	list = ft_strsplit(path, ':');
	while (list[i])
	{
		ft_get_path(list[i], &root, &len, find);
		free(list[i]);
		i++;
	}
	if (list == NULL)
		free(list);
	return (ft_add_block(&root, &len));
}
