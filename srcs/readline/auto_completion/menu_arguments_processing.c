/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_arguments_processing.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 14:15:33 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/26 21:19:29 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

char				*find_path_compl(char *full_raw_line, int last_slash)
{
	char			*path;
	char			*tmp_path;

	if (g_rline.pos <= 0)
		return (NULL);
	path = NULL;
	tmp_path = ft_strndup(full_raw_line, last_slash + 1);
	if (tmp_path && tmp_path[0] && tmp_path[0] == '~')
	{
		path = ft_parsing_str(tmp_path);
		free(tmp_path);
		tmp_path = path;
	}
	else if (tmp_path && tmp_path[0] && tmp_path[0] == '.')
	{
		path = ft_new_path_cd(tmp_path, NULL, NULL);
		free(tmp_path);
		tmp_path = path;
	}
	path = make_final_path_compl(tmp_path);
	free(tmp_path);
	return (path);
}

char				*make_final_path_compl(char *path)
{	
	char			*new_path;
	char			*tmp_path;
	char			**arr;

	if (!(path && path[0]))
		return (NULL);
	if (path[0] == '/' && !path[1])
		return (ft_strdup("/"));
	new_path = NULL;
	tmp_path = make_temporal_path_compl(path);
	arr = ft_strsplit(tmp_path, '/');
	if (!(arr && arr[0]))
	{
		free(tmp_path);
		return (NULL);
	}
	free(arr[0]);
	arr[0] = ft_strdup("/");
	free(tmp_path);
	new_path = ft_new_from_arr_cd(arr);
	ft_arrdel(arr);
	if (new_path[ft_strlen(new_path) - 1] != '/')
		new_path = ft_strrejoin(new_path, "/");
	return (new_path);
}

char				*make_temporal_path_compl(char *path)
{
	char			*tmp_path;
	char			*first_slash;

	first_slash = NULL;
	if (path[0] == '/' && path[1])
		first_slash = path + 1;
	tmp_path = ft_strdup("1");
	tmp_path = ft_strrejoin(tmp_path, "/");
	tmp_path = ft_strrejoin(tmp_path, first_slash);
	return (tmp_path);
}
