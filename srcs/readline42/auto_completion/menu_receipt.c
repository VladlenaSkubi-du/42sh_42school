/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_receipt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:17:28 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/05 14:11:53 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

char				**get_variables(char *complete, size_t *total, int *max_len)
{
	char			**menu;
	t_path			*root;
	size_t			len;

	len = ft_strlen(complete);
	root = fill_tree_with_variables(complete, total, len);
	menu = ft_add_block(&root, *total, max_len);
	ft_path_free(&root);
	return (menu);
}

int					insert_variables_to_tree(char *array, char *complete,
						t_path **root, size_t *total)
{
	char			*tmp;
	size_t			len;

	len = ft_strlen(complete);
	tmp = ft_strndup(array, ft_strchri(array, '='));
	if (ft_strnequ(tmp, complete, len))
		insert(tmp, root, total);
	free(tmp);
	return (0);
}

t_path				*fill_tree_with_variables(char *complete,
						size_t *total, size_t len)
{
	size_t			i;
	t_path			*root;

	i = 0;
	root = NULL;
	while (g_env[i])
	{
		insert_variables_to_tree(g_env[i], complete, &root, total);
		i++;
	}
	i = 0;
	while (g_shvar[i])
	{
		insert_variables_to_tree(g_shvar[i], complete, &root, total);
		i++;
	}
	i = 0;
	while (g_lovar[i])
	{
		insert_variables_to_tree(g_lovar[i], complete, &root, total);
		i++;
	}
	return (root);
}

char				**get_arguments(char **complete,
						size_t *total, int *max_len)
{
	char			**menu;
	char			*path;
	char			*compl;
	int				tmp;
	t_path			*root;

	tmp = ft_strchri(*complete, '/');
	path = find_path_compl(*complete, tmp);
	compl = (tmp >= 0 && tmp < ft_strlen(*complete))
			? ft_strdup(*complete + tmp + 1) : NULL;
	if (compl != NULL)
	{
		free(*complete);
		*complete = compl;
	}
	root = fill_tree_with_arguments(path, *complete, total);
	if (root == NULL)
	{
		free(path);
		return (NULL);
	}
	menu = ft_add_block(&root, *total, max_len);
	ft_path_free(&root);
	free(path);
	return (menu);
}

t_path				*fill_tree_with_arguments(char *path,
						char *complete, size_t *total)
{
	size_t			i;
	t_path			*root;
	size_t			len;
	DIR				*dir_name;
	struct dirent	*entry;

	i = 0;
	root = NULL;
	if (path == NULL)
		return (NULL);
	len = ft_strlen(complete);
	if (!(dir_name = opendir(path)))
		return (NULL);
	while ((entry = readdir(dir_name)))
	{
		if (entry->d_name[0] == '.')
			continue ;
		if (ft_strnequ(entry->d_name, complete, len))
			insert(entry->d_name, &root, total);
	}
	closedir(dir_name);
	return (root);
}
