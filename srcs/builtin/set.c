/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 16:57:49 by rbednar           #+#    #+#             */
/*   Updated: 2020/03/12 18:49:47 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

static int	sorting_vars(t_path **root, size_t *len)
{
	size_t	i;

	i = -1;
	while (g_env[++i])
		insert(g_env[i], root, len);
	i = -1;
	while (g_shvar[++i])
		insert(g_shvar[i], root, len);
	i = -1;
	while (g_lovar[++i])
		insert(g_lovar[i], root, len);
	i = -1;
	while (g_rdovar[++i])
		insert(g_rdovar[i], root, len); //нужны ли эти переменные в set?
	return (0);	
}

int			btin_set(void)
{
	t_path	*root;
	char	**list;
	size_t	len;
	int 	max;

	root = NULL;
	list = NULL;
	len = 0;
	sorting_vars(&root, &len);
	list = ft_add_block(&root, len, &max);
	ft_path_free(&root);
	max = -1;
	while(list[++max])
		ft_putendl(list[max]);
	ft_arrdel(list);
	return (0);	
}