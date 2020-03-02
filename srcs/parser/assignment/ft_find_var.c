/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 12:58:47 by rbednar           #+#    #+#             */
/*   Updated: 2020/03/02 18:14:20 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

/*
** Function finds and substitudes classic vars of type "$PATH"
*/

int		ft_find_var(t_ltree *sub)
{
	size_t	i;
	size_t	size;
	char	*find;

	i = -1;
	while (++i < sub->l_tline.len)
	{
		if (sub->l_tline.line[i] == DOLLAR &&
		sub->l_tline.line[i + 1] != OBRACE && sub->l_tline.line[i + 1] != OPAREN)
		{
			size = 1;
			while (i + size < sub->end && sub->l_tline.line[i + size] == WORD_P)
				size++;
			find = ft_strndup(&sub->l_cmd[i + 1], size - 1);
			if ((find = ft_find_var_value(&find)) != NULL)
			{
				ft_reglue(&i, size - 1, sub);
				insert_str_in_loc_strs(sub, &find, &i, TEXT);
			}		
			else
				ft_reglue(&i, size, sub);
		}
	}
	return (0);
}

char	*ft_find_var_value(char **find)
{
	size_t	li;
	size_t	sj;
	char	*res;
	
	li = -1;
	sj = -1;
	res = NULL;
	if ((li = find_in_variables(g_env, &sj, *find)) != -1)
		res = ft_strdup(&g_env[li][sj]);
	if ((li = find_in_variables(g_shvar, &sj, *find)) != -1)
		res = ft_strdup(&g_shvar[li][sj]);
	if ((li = find_in_variables(g_lovar, &sj, *find)) != -1)
		res = ft_strdup(&g_lovar[li][sj]);
	free(*find);
	return (res);	
}
