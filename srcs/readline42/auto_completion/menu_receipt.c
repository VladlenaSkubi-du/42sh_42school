/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_receipt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:17:28 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/29 11:20:17 by sschmele         ###   ########.fr       */
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

t_path				*fill_tree_with_variables(char *complete,
						size_t *total, size_t len)
{
	size_t			i;
	t_path			*root;
	char			*tmp;

	i = 0;
	root = NULL;
	while (g_env[i])
	{
		tmp = ft_strndup(g_env[i], ft_strchri(g_env[i], '='));
		if (ft_strnequ(tmp, complete, len))
			insert(tmp, &root, total);
		free(tmp);
		i++;
	}
	i = 0;
	while (g_shvar[i])
	{
		tmp = ft_strndup(g_shvar[i], ft_strchri(g_shvar[i], '='));
		if (ft_strnequ(tmp, complete, len))
			insert(tmp, &root, total);
		free(tmp);
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
