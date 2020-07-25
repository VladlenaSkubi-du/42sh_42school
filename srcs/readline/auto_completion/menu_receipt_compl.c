/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_receipt_compl.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 17:08:13 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/25 17:08:35 by sschmele         ###   ########.fr       */
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

char				**get_arguments(char **complete,
						int *total, int *max_len)
{
	char			**menu;
	char			*path;
	char			*compl;
	int				tmp;
	t_path			*root;

	tmp = ft_strrchri(*complete, '/');
	path = find_path_compl(*complete, tmp);
	compl = (tmp >= 0 && tmp < (int)ft_strlen(*complete))
			? ft_strdup(*complete + tmp + 1) : ft_strdup(*complete);
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
	menu = ft_add_block(&root, (size_t)*total, max_len);
	ft_path_free(&root);
	free(path);
	return (menu);
}

char				*find_path_compl(char *compl, int tmp)
{
	char			*path;
	char			*temp;

	if (g_rline.pos <= 0)
		return (NULL);
	if (compl && compl[0] && tmp >= 0)
	{
		temp = (tmp == 0) ? ft_strdup("/") : ft_strndup(compl, tmp + 1);
		if (ft_isalnum(compl[0]))
		{
			path = ft_strjoin("./", temp);
			free(temp);
		}
		else
		{
			make_one_slash(&temp, tmp, compl);
			path = temp;
		}
	}
	else
		path = ft_strdup("./");
	return (path);
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
