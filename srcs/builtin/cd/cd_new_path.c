/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_new_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 16:08:55 by kfalia-f          #+#    #+#             */
/*   Updated: 2020/08/27 20:13:47 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>
#include <builtin42.h>

void		ft_del_prev(char **arr, int i)
{
	while (i > 0)
	{
		if (ft_strcmp(arr[i], ".") && ft_strcmp(arr[i], ".."))
		{
			free(arr[i]);
			arr[i] = ft_strdup(".");
			break ;
		}
		i--;
	}
}

void		ft_del_dots(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		if (ft_strcmp(arr[i], "..") == 0)
			ft_del_prev(arr, i);
		i++;
	}
}

char		*ft_new_from_arr_cd(char **arr)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_memalloc(1);
	ft_del_dots(arr);
	while (arr[i])
	{
		if (ft_strcmp(arr[i], ".") && ft_strcmp(arr[i], ".."))
		{
			if (i > 1)
				tmp = ft_strrejoin(tmp, "/");
			tmp = ft_strrejoin(tmp, arr[i]);
		}
		i++;
	}
	return (tmp);
}

int			ft_del_slash_cd(char **path)
{
	int		i;
	int		j;
	char	tmp[MAXDIR];
	int		count;

	i = -1;
	count = 0;
	j = 0;
	while ((*path)[++i])
	{
		if ((*path)[i] == '/' && count > 0)
			continue ;
		else if ((*path)[i] == '/')
			count++;
		else
			count = 0;
		tmp[j++] = (*path)[i];
		if (j + 1 == MAXDIR)
			break ;
	}
	tmp[j] = '\0';
	free(*path);
	*path = ft_strdup(tmp);
	return (0);
}

char		*ft_new_path_cd(char *path, char *src_path, t_cd *flags)
{
	char	*new_path;
	char	*tmp;
	char	**arr;

	if (!(path || path[0]))
		return (NULL);
	if (path[0] == '/' && !(path[1]))
		return (ft_strdup("/"));
	if (path[0] == '/' && path[1])
		tmp = make_temporal_path_compl(path);
	else
		tmp = ft_join_cd(path, src_path, flags);
	arr = ft_strsplit(tmp, '/');
	if (!(arr && arr[0]))
	{
		free(tmp);
		return (NULL);
	}
	free(arr[0]);
	arr[0] = ft_strdup("/");
	free(tmp);
	new_path = ft_new_from_arr_cd(arr);
	ft_del_slash_cd(&new_path);
	ft_arrdel(arr);
	return (new_path);
}
