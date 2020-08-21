/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 16:00:12 by hshawand          #+#    #+#             */
/*   Updated: 2020/08/21 19:31:16 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

char	**path_parse(void)
{
	char	**ret;
	int		li;
	int		co;

	ret = NULL;
	li = find_in_variable(&co, "PATH");
	if (li < 0 || ((ret = ft_strsplit(&g_envi[li][co], ':')) == NULL) ||
			ret[0] == NULL || ret[0][0] == '\0')
	{
		ft_arrdel(ret);
		return (NULL);
	}
	return (ret);
}

char	*form_path(char *ret, char *env_path, char *name)
{
	ft_strcpy(ret, env_path);
	if (!(env_path[ft_strlen(env_path) - 1] == '/'))
		ft_strcat(ret, "/");
	ft_strcat(ret, name);
	return (ret);
}

char	*locate_file(char *env_path, char *name)
{
	struct dirent	*entity;
	char			*ret;
	DIR				*path;

	ret = NULL;
	path = opendir(env_path);
	if (path == NULL)
		return (NULL);
	while ((entity = readdir(path)))
	{
		if (!ft_strcmp(entity->d_name, name))
		{
			ret = (char*)ft_xmalloc(ft_strlen(env_path) + ft_strlen(name) + 2);
			ret = form_path(ret, env_path, name);
			if (ret)
				break ;
		}
	}
	closedir(path);
	return (ret);
}

/*
** This is "just executable name case". We should
** check all directories in $PATH, find first match
** and check its accessibility
*/

char	*path_search(char *name)
{
	char			**path_array;
	char			**to_clean;
	char			*ret;

	ret = NULL;
	if (!(path_array = path_parse()))
		return (NULL);
	to_clean = path_array;
	while (*path_array)
	{
		ret = locate_file(*path_array, name);
		if (ret)
			break ;
		path_array++;
	}
	ft_arrdel(to_clean);
	return (ret);
}

/*
** Here we should find check and return execpath
*/

char	*path_init(char **exec_av)
{
	char 		*ret;

	if (!ft_strchr(*exec_av, '/'))
		ret = hashtable_cmd_init(*exec_av);
	else
	{
		if (path_init_errors(*exec_av) < 0)
			return (NULL);
		ret = ft_strdup(exec_av[0]);
	}
	return (ret);
}
