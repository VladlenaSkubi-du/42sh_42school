/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_arguments_processing.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 14:15:33 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/26 17:07:28 by sschmele         ###   ########.fr       */
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
	path = make_final_path_compl(tmp_path);
	return (path);
}

char				*make_final_path_compl(char *path)
{	
	char			*new_path;
	char			*tmp_path;
	char			*first_slash;
	char			**arr;

	if (!(path || path[0]))
		return (NULL);
	if (path[0] == '/' && !path[1])
		return (ft_strdup("/"));
	first_slash = NULL;
	if (path[0] == '/' && path[1])
		first_slash = path + 1;
	tmp_path = ft_strdup("1");
	tmp_path = ft_strrejoin(tmp_path, "/");
	tmp_path = ft_strrejoin(tmp_path, first_slash);
	arr = ft_strsplit(tmp_path, '/');
	free(arr[0]);
	arr[0] = ft_strdup("/");
	free(tmp_path);
	new_path = ft_new_from_arr_cd(arr);
	ft_arrdel(arr);
	if (new_path[ft_strlen(new_path) - 1] != '/')
		new_path = ft_strrejoin(new_path, "/");
	return (new_path);
}

int					make_one_slash(char **final, int last_slash, char *compl)
{
	int				check;
	int				i;

	check = last_slash;
	i = check;
	while (i >= 0)
	{
		if (compl[i] == '/')
		{
			i = check;
			while (i >= 0 && compl[i] == '/')
				i--;
			if (i < check)
				ft_strshift((*final) + check, i - check + 1);
		}
		i--;
		check = i;
	}
	return (0);
}

int					make_tilda_expansion(char **final, char *compl)
{
	char			*home_env;
	char			*find;
	
	if ((home_env = find_env_value("HOME")) == NULL)
		find = ft_home_from_etcpasswd();
	else
		find = ft_strdup(home_env);
	if (*final)
		free(*final);
	printf("len_find = %zu, len_compl = %zu\n", ft_strlen(find), ft_strlen(compl));
	*final = (char*)ft_xmalloc(ft_strlen(find) + ft_strlen(compl) + 1);
	ft_strcpy(*final, find);
	if (compl && compl[0])
		ft_strcat(*final, compl);
	printf("final = %s\n", *final);
	return (0);
}