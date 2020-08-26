/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_receipt_compl.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 17:08:13 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/26 17:15:47 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

char				**get_variables(char *complete, int *total, int *max_len)
{
	char			**menu;
	t_path			*root;

	root = fill_tree_with_variables(complete, total);
	menu = ft_add_block(&root, (size_t)*total, max_len);
	ft_path_free(&root);
	return (menu);
}

t_path				*fill_tree_with_variables(char *complete, int *total)
{
	int				i;
	t_path			*root;
	char			*name;
	int				len;

	i = 0;
	root = NULL;
	while (g_envi[i])
	{
		if (g_envi[i][0] && (g_envi[i][0] & SET_VIS))
		{
			len = ft_strlen(complete);
			name = ft_strndup(g_envi[i] + 1,
					ft_strchri(g_envi[i] + 1, '='));
			if (ft_strnequ(name, complete, len))
				insert_in_bintree(name, &root, (size_t*)total);
			free(name);
		}
		i++;
	}
	return (root);
}

/*
** @compl can be a string or NULL
*/

char				**get_arguments(char *full_raw_line,
						int *total, int *max_len)
{
	char			*path;
	char			*compl;
	int				last_slash;
	char			**menu;

	last_slash = ft_strrchri(full_raw_line, '/');
	path = NULL;
	compl = NULL;
	if (last_slash < 0)
	{
		path = ft_strdup("./");
		compl = (full_raw_line && full_raw_line[0]) ?
			ft_strdup(full_raw_line) : NULL;
	}
	else
	{
		path = find_path_compl(full_raw_line, last_slash);
		compl = (full_raw_line && full_raw_line[last_slash + 1]) ?
			ft_strdup(full_raw_line + last_slash + 1) : NULL;
	}
	menu = get_arguments_by_path_compl(path, compl, total, max_len);
	free(path);
	free(compl);
	return (menu);
}

char				**get_arguments_by_path_compl(char *path, char *compl,
						int *total, int *max_len)
{
	char			**menu;
	t_path			*root;

	root = fill_tree_with_arguments(path, compl, total);
	if (root == NULL)
		return (NULL);
	menu = ft_add_block(&root, (size_t)*total, max_len);
	ft_path_free(&root);
	return (menu);
}

t_path				*fill_tree_with_arguments(char *path,
						char *complete, int *total)
{
	t_path			*root;
	int				len;
	DIR				*dir_name;
	struct dirent	*entry;

	root = NULL;
	if (path == NULL || path[0] == '\0')
		return (NULL);
	len = ft_strlen(complete);
	if (!(dir_name = opendir(path)))
		return (NULL);
	while ((entry = readdir(dir_name)))
	{
		if ((entry->d_name[0] == '.' && entry->d_name[1] == '\0') ||
				(entry->d_name[0] == '.' && entry->d_name[1] &&
				entry->d_name[1] == '.' && entry->d_name[2] == '\0') ||
				ft_isprint(entry->d_name[0]) == 0)
			continue ;
		if (ft_strnequ(entry->d_name, complete, len))
			insert_in_bintree(entry->d_name, &root, (size_t*)total);
	}
	closedir(dir_name);
	return (root);
}
