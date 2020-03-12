/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 16:54:47 by rbednar           #+#    #+#             */
/*   Updated: 2020/03/12 20:43:36 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"
#include "buildins_list.h"

/*
** Functions to insert t_path element prev or next
*/

int			ft_insert_prev(t_path **current, t_path **parent, \
	t_path **temp, size_t *len)
{
	*current = (*current)->prev;
	if (*current == NULL)
	{
		(*parent)->prev = *temp;
		(*len) += 1;
		return (0);
	}
	return (1);
}

int			ft_insert_next(t_path **current, t_path **parent, \
	t_path **temp, size_t *len)
{
	*current = (*current)->next;
	if (*current == NULL)
	{
		(*parent)->next = *temp;
		(*len) += 1;
		return (0);
	}
	return (1);
}

/*
** Input buildins to tree
*/

int			ft_input_buildins(t_path **root, size_t *len, char *find)
{
	int		i;
	size_t	str_len;

	i = 0;
	str_len = ft_strlen(find);
	g_buildins_func[14] = NULL;
	while (g_buildins[i])
	{
		if (ft_strnequ(g_buildins[i], find, str_len))
			insert(g_buildins[i], root, len);
		i++;
	}
	return (0);
}

/*
** Function to free tree t_path
*/

int			ft_path_free(t_path **root)
{
	if (root != NULL && *root != NULL)
	{
		ft_path_free(&((*root)->next));
		free((*root)->name);
		ft_path_free(&((*root)->prev));
		free(*root);
	}
	return (0);
}
