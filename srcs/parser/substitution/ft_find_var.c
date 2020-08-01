/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 16:02:06 by rbednar           #+#    #+#             */
/*   Updated: 2020/08/01 16:07:13 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

/*
** Function finds and substitudes classic vars of type "$PATH"
*/

int		ft_find_var(t_ltree *sub)
{
	int		i;
	int		size;
	char	*find;

	i = -1;
	while ((size_t)++i < sub->l_tline.len)
	{
		if (sub->l_tline.line[i] == DOLLAR && sub->l_tline.line[i + 1] != OBRACE
			&& sub->l_tline.line[i + 1] != OPAREN)
		{
			size = 1;
			while (i + size < sub->end && sub->l_cmd[i + size] != '/'
				&& sub->l_tline.line[i + size] == WORD_P)
				size++;
			find = size > 1 ? ft_strndup(&sub->l_cmd[i + 1], size - 1) : NULL;
			if ((find = ft_find_var_value(&find)) != NULL)
			{
				ft_reglue(&i, size - 1, sub);
				insert_str_in_loc_strs(sub, &find, &i, TEXT);
			}
			else if (size > 1)
				ft_reglue(&i, size, sub);
		}
	}
	return (0);
}

/*
** Function finds and substitudes vars of type "${parameter}"
*/

int		ft_find_curv_var(t_ltree *sub)
{
	int		i;
	int		size;
	char	*find;

	i = -1;
	while ((size_t)++i < sub->l_tline.len)
	{
		if (sub->l_tline.line[i] == DOLLAR &&
			sub->l_tline.line[i + 1] == OBRACE)
		{
			size = 2;
			while (i + size < sub->end && sub->l_tline.line[i + size] != CBRACE)
				size++;
			find = ft_strndup(&sub->l_cmd[i + 2], size - 2);
			return (ft_type_param_check(sub, &find, &i));
		}
	}
	return (0);
}

char	*ft_find_var_value(char **find)
{
	char	*res;

	res = ft_strdup(find_env_value(*find));
	free(*find);
	return (res);
}

int		ft_param_empty(t_ltree *sub, char **find, int *i)
{
	char	*tmp;
	size_t	size;

	size = ft_strlen(*find);
	if ((tmp = ft_find_var_value(find)) != NULL)
	{
		ft_reglue(i, size + 2, sub);
		insert_str_in_loc_strs(sub, &tmp, i, TEXT);
	}
	else
		ft_reglue(i, size + 3, sub);
	return (0);
}

int		ft_error_vars(t_ltree *sub, int err, char *msg)
{
	sub->flags |= ERR_OUT;
	sub->err_i |= err;
	if (msg)
		sub->err = ft_strdup(msg);
	if (!(sub->err_i & ERR_UNSET << 9 || sub->err_i & ERR_SET << 9))
		sub->err_i |= ERR_RDONLY << 9;
	error_handler(sub->err_i, sub->err);
	return (err);
}
