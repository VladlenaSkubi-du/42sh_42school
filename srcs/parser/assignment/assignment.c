#include "shell42.h"
#include "parser.h"

int		assignment(t_ltree *sub)
{
	int		i;
	int		len_arg;
	char	**arg_tline;

	argv_forming(sub);
	arg_tline = ft_strsplit(sub->l_tline.line, SPACE);
	i = 0;
	while (i < sub->ar_c)
	{
		len_arg = ft_strlen(sub->ar_v[i]);
		if (check_kind_assign(sub, i, len_arg, arg_tline))
			break ;
		i++;
	}
	if (i == 0)
	{
		ft_arrdel(arg_tline);
		return (0);
	}	
	if (i < sub->ar_c)
	{
		add_new_local_env(sub, i, arg_tline);
		return (form_local_str_from_arrays(sub, 0, arg_tline));
	}
	return (add_vars_to_genvi(sub, arg_tline));
}

/*
** Functions returns 1 if in argv is COMMAND and 0 if assignment
** So we check, if some local assignments before command or we have
** only assignments, or have no one assignment
*/

int		check_kind_assign(t_ltree *sub, int i, int len_arg, char **arg_tline)
{
	size_t 	eq;

	eq = 0;
	while (eq < len_arg)
	{
		if (arg_tline[i][eq] == EQUAL)
			break ;
		eq++;
	}
	if (eq < len_arg)
	{
		if (is_it_command(sub, i, arg_tline, eq))
			return(1);
		return (0);
	}
	return (1);
}

/*
** If in the start of arg is "=", this means that arg is command
*/

int		is_it_command(t_ltree *sub, int i, char **arg_tline, int eq)
{
	if (eq == 0)
		return (1);
	return (0);
}

/*
** Adding new variable to the environ of the command to be executed
** First we try to find if it already exists and insert if it is found
** Then we add if the @add is a new variable
*/

int		add_new_local_env(t_ltree *sub, int i, char **arg_tline)
{
	char	*find;
	int		start;
	int		eq;

	if (!sub->envir)
		sub->envir = ft_xmalloc(sizeof(char*));
	form_local_envir(&(sub->envir), 0);
	sub->envir = ft_realloc_array(&(sub->envir), g_var_size, g_var_size + i);
	start = -1;
	while (++start < i)
	{
		eq = ft_strchri(arg_tline[start], EQUAL);
		find = ft_strndup(sub->ar_v[0], eq);
		assign_local_or_err(sub, find, 0);
		free(find);
		unset_from_array(&sub->ar_v, 0);
		sub->ar_c--;
	}
	return (0);
}

int		assign_local_or_err(t_ltree *sub, char *find, int start)
{
	int		i;
	int		j;

	if ((i = find_in_variable(&j, find)) != -1)
	{
		if (g_envi[i][0] & READONLY)
			error_handler(ERR_RDONLY << 9 | VARIABLE_ERROR, find);
		else
			change_var_in_local(sub, find, start);
	}
	else
		new_var_in_local(sub, start);
	return (0);
}
