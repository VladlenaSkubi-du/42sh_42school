/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 16:00:12 by hshawand          #+#    #+#             */
/*   Updated: 2020/08/09 17:57:43 by rbednar          ###   ########.fr       */
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
	char *ret;

	if (!ft_strchr(*exec_av, '/'))
		ret = hashtable_cmd_init(*exec_av);
	else
	{
		if (access(*exec_av, F_OK) == -1)
		{
			error_handler(COMMAND_NOT_FOUND |
				(ERR_NO_FILE << 9), *exec_av);
			return (NULL);
		}
		else if (access(*exec_av, X_OK) == -1)
		{
			error_handler(COMMAND_NON_EXECUTABLE, *exec_av);
			return (NULL);
		}
		ret = ft_strdup(exec_av[0]);
	}
	return (ret);
}
