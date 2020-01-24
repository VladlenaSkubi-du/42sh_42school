/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_receipt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:17:28 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/24 12:27:46 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

char			*path_parse_compl(void)
{
	size_t		i;

	i = 0;
	while (g_env[i])
	{
		if (ft_strncmp(g_env[i], "PATH=", 5) == 0)
			return (g_env[i] + 5);
		i++;
	}
	return (NULL);
}

char			**get_variables(char *complete, size_t *total, int *max_len)
{
	char		**menu = NULL;
	t_path		*root;
	size_t		len;

	len = ft_strlen(complete);
	root = fill_tree_with_variables(complete, total, len);
	menu = ft_add_block(&root, *total, max_len);
	ft_path_free(&root);
	return (menu);
}

t_path			*fill_tree_with_variables(char *complete, size_t *total, size_t len)
{
	size_t		i;
	t_path		*root;
	char		*tmp;

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

char			**get_arguments(char *complete, size_t *total, int *max_len)
{
	char		**menu = NULL;
	// printf("%s\n", complete);
	t_path		*root;
	size_t		len;

	len = ft_strlen(complete);
	root = fill_tree_with_arguments(complete, total, len);
	if (root == NULL)
		return (NULL);
	menu = ft_add_block(&root, *total, max_len);
	ft_path_free(&root);
	return (menu);
}

t_path			*fill_tree_with_arguments(char *complete, size_t *total, size_t len)
{
	size_t		i;
	t_path		*root;
	DIR			*dir_name;
	char		*path;

	i = 0;
	root = NULL;
	
	return(root);
}
