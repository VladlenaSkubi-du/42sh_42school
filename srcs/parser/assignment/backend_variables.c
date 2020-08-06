/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backend_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:35:34 by rbednar           #+#    #+#             */
/*   Updated: 2020/08/06 18:43:52 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

/*
** Is used in parser to execute the assignment command "VARIABLE=VALUE"
** Checks the array if such variable exists and if not found -
** adds the variable to @g_envi
** READONLY can not be changed by the user, therefore if the variable
** is one of the rdonly shell variables - there is an error
*/

int			find_assignment_in_vars(char *sub, size_t var,
				size_t eq, size_t val)
{
	int		li;
	int		sy;
	char	*find;
	char	*new_var;

	find = ft_strndup(sub + var, val - var + 1);
	new_var = ft_parsing_str(find);
	free(find);
	find = ft_strndup(sub + var, eq - var);
	if ((li = find_in_variable(&sy, find)) != -1)
	{
		if (g_envi[li][0] & READONLY)
			g_envi[li][0] |= ENV_VIS;
		else
			change_env_value(new_var, li);
	}
	else
		add_new_env(new_var);
	free(new_var);
	free(find);
	if (li != -1 && g_envi[li][0] & READONLY)
		return (ERR_OUT);
	return (0);
}

int			assignment_in_curv_var(t_ltree *sub, char **line,
				char *oper, int *i)
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
	if ((j = find_assignment_in_vars(*line, 0, j, ft_strlen(*line))) ==
		(ERR_OUT))
		sub->err = ft_strndup(*line, ft_strchri(*line, '='));
	free(*line);
	insert_str_in_loc_strs(sub, &buf, i, TEXT);
	return (sub->err_i |= j);
}

int			ft_colon_check(int *len, char **line, char **oper, size_t *j)
{
	*len = ft_strlen(*line);
	if ((*j = ft_strchri(*line, ':')) != (size_t)-1)
	{
		ft_memmove(&(line[0][*j]), &(line[0][*j + 1]), *len - *j);
		line[0][--(*len)] = '\0';
		*oper -= 1;
		(*len)++;
	}
	return (0);
}

int			ft_alias_find(t_ltree *sub)
{
	char	*name;
	char	*ans;
	int		i;

	if ((name = sub->ar_v[0]))
		if (btin_alias_init(&name, &ans, ASSIGN) != OUT)
		{
			i = ft_strstr(sub->l_cmd, name) - sub->l_cmd;
			name = ft_strdup(&ans[ft_strlen(name) + 1]);
			ft_reglue(&i, ft_strlen(sub->ar_v[0]) - 1, sub);
			free(sub->l_tline.line);
			ft_get_techline(sub->l_cmd, &(sub->l_tline));
			insert_str_in_loc_strs(sub, &name, &i, 0);
			ft_arrdel(sub->ar_v);
			argv_forming(sub);
			free(ans);
		}
	return (0);
}
