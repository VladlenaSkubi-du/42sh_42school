/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 15:36:08 by rbednar           #+#    #+#             */
/*   Updated: 2019/12/26 17:50:35 by rbednar          ###   ########.fr       */
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
		temp->name = dp->d_name;
		temp->path = dp->d_name;
		temp->path = ft_take_path(name, temp);
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

static t_path	*ft_insert_in(char *name, t_path *root)
{
	t_path	*current;
	t_path	*parent;

	current = root;
	parent = NULL;
	while (1)
	{
		parent = current;
		if (name == parent->name)
			return (NULL);
		else if (name < parent->name)
		{
			current = current->prev;
			if (current == NULL)
				return (parent->prev);
		}
		else
		{
			current = current->next;
			if (current == NULL)
				return (parent->next);
		}
	}
}

/*
** Func insert t_path element by *root element in all conditions
*/

static void		insert(char *name, t_dirent *dp,  t_path *root)
{
	t_path	*temp;
	t_path	*current;

	temp = ft_init_path(name, dp);
	if (root == NULL)
		root = temp;
	else
	{
		current = ft_insert_in(name, dp,  root);
		if (current)
			current = temp;
		else
			free(temp);
	}
}

/*
** Func finds files in dir and add it to tree of type t_path
*/

void		ft_get_path(char *name, t_path *root, size_t *len)
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
	while (dir)
	{
		if ((dp = readdir(dirp)) != NULL)
		{
			insert(name, dp, root);
			(*len)++;
		}
		else
			closedir(dir) == 0 ? dir = NULL : 0;
	}
	free(stat_b);
}

/*
** Func insert t_path element by *root element in all conditions
*/

char 		**ft_path_pars(char *path)
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
		ft_get_path(list[i], root, &len);
		free(list[i]);
		i++;
	}
	if (list == NULL)
		free(list);
	return (ft_add_block(root, len));
}
