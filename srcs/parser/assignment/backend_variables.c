/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backend_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:56:28 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/05 20:50:55 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

int			find_assignment_in_variables(char *sub, size_t var,
				size_t eq, size_t val)
{
	size_t		li;
	size_t		sy;
	char		*find;

	li = -1;
	sy = -1;
	find = ft_strndup(sub + var, eq - var);
	if ((li = find_in_variables(g_rdovar, &sy, find)) != -1)
		return (ERR_OUT | VARIABLE_ERROR); //выход из парсера в ридлайн
	if ((li = find_in_variables(g_env, &sy, find)) != -1)
		return (insert_assign_to_arrays(find, ft_strndup(sub + var,
			val - var),	&g_env[li]));
	else if ((li = find_in_variables(g_shvar, &sy, find)) != -1)
	{
		insert_assign_to_arrays(find, ft_strndup(sub + var, val - var),
			&g_shvar[li]);
		return (check_if_histsize_changed());
	}
	else if ((li = find_in_variables(g_lovar, &sy, find)) != -1)
		return (insert_assign_to_arrays(find, ft_strndup(sub + var,
			val - var), &g_lovar[li]));
	free(find);
	find = ft_strndup(sub + var, val - var);
	save_local_variables(find);
	return (0);
}

int				insert_assign_to_arrays(char *find, char *insert,
					char **array)
{
	free(find);
	free(*array);
	*array = insert;
	return (0);
}

int			assignment_in_curv_var(t_ltree *sub, char **line,
				char *oper, size_t *i)
{
	size_t	j;
	int		len;
	char	*buf;
	
	ft_colon_check(&len, line, &oper, &j);
	buf = ft_parsing_str(oper + 1);
	ft_reglue(i, len + 2, sub);
	oper[1] = '\0';
	j = oper - *line;
	*line = ft_strrejoin(*line, buf);
	if ((j = find_assignment_in_variables(*line, 0, j, ft_strlen(*line))) ==
		(ERR_OUT | VARIABLE_ERROR))
		sub->err = ft_strndup(*line, ft_strchri(*line, '='));
	free (*line);
	insert_str_in_loc_strs(sub, &buf, i, TEXT);
	return (sub->err_i |= j);
}

int			ft_colon_check(int *len, char **line, char **oper, size_t *j)
{
	*len = ft_strlen(*line);
	if ((*j = ft_strchri(*line, ':')) != -1)
	{
		ft_memmove(&(line[0][*j]), &(line[0][*j + 1]), *len - *j);
		line[0][--(*len)] = '\0';
		*oper -= 1;
		(*len)++;
	}
	return (0);
}
