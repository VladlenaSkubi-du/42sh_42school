/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 20:20:14 by rbednar           #+#    #+#             */
/*   Updated: 2020/03/06 22:47:31 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

int		assignment(t_ltree *sub)
{
	size_t 	eq;
	size_t	var;
	size_t	val;

	eq = 0;
	while (eq < sub->l_tline.len)
	{
		if (sub->l_tline.line[eq] == EQUAL)
		{
			var = eq - 1;
			val = eq + 1;
			while (sub->l_tline.line[var] != SPACE && var > 0 && var != -1)
				var--;
			var++;
			while (sub->l_tline.line[val] != SPACE && val < sub->l_tline.len)
				val++;
			val--;
			get_assign_and_add(sub, &var, &eq, &val);
		}
		eq++;
	}
	return (0);
}

int		get_assign_and_add(t_ltree *sub, size_t *var, size_t *eq, size_t *val)
{
	size_t	i;
	char	*buf;

	if (*var == *eq)
	{
		i = sub->start;
		while (i < *var && sub->l_tline.line[i] == SPACE)
			i++;
		if (i == *var)
			ft_reglue(&i, 1, sub);
		return (0);
	}
	i = *val;
	while (i < sub->l_tline.len && sub->l_tline.line[i] == SPACE)
		i++;
	if (i == sub->l_tline.len)
		return (find_assignment_in_variables(sub->l_cmd, *var, *eq, *val));
	else
	{
		buf = ft_strndup(sub->l_cmd + *var, *val - *var);
		add_new_to_exec_env(&(sub->envir), &buf);
		ft_reglue(var, *val - *var, sub);
		*eq = *var - 1;
	}
	return (0);
}
