/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 20:24:41 by rbednar           #+#    #+#             */
/*   Updated: 2020/08/07 20:24:42 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"
#include "builtins_list.h"

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
** Input builtins to tree
*/

int			ft_input_builtins(t_path **root, size_t *len, char *find)
{
	int		i;
	size_t	str_len;

	i = 0;
	str_len = ft_strlen(find);
	g_builtins_func[BUILTINS_NUM - 1] = NULL;
	while (g_builtins[i])
	{
		if (ft_strnequ(g_builtins[i], find, str_len))
			insert_in_bintree(g_builtins[i], root, len);
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
