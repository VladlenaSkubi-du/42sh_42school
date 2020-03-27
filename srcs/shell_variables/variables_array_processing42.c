#include "shell42.h"

/*
** Adding new to @g_env (shell environment)
** Can be done only with builtin export (export FOO=bar)
*/

int				add_to_environment_variables(char *add)
{
	size_t		num;
	
	num = 0;
	while (g_env[num])
		num++;
	(num == g_var_size) ? realloc_all_gvariables_array() : 0;
	g_env[num] = ft_strdup(add);
	return (0);
}

/*
** Adding new to @g_lovar (shell local variables)
** Can be done only by assignment (foo=bar)
** @add is already malloced - can come only from find_assignment_in_vars
*/

int				add_to_local_variables(char *add)
{
	size_t		num;
	
	num = 0;
	while (g_lovar[num])
		num++;
	if (num == g_var_size)
		realloc_all_gvariables_array();
	g_lovar[num] = add;
	return (0);
}

/*
** Adding new variable to the environ of the command to be executed
** First we try to find if it already exists and insert if it is found
** Then we add if the @add is a new variable
*/

int				add_new_to_exec_env(char ***array, char **add)
{
	size_t		i;
	size_t		li;
	size_t		sy;
	char		*find;

	i = 0;
	find = ft_strndup(*add, ft_strrchri(*add, '='));
	if ((li = find_in_variables(g_env, &sy, find)) != -1)
		return (insert_assign_to_arrays(find, *add,	&g_env[li]));
	else
	{
		while (array[0][i])
			i++;
		if (i == g_var_size)
		{
			ft_realloc_array(array, g_var_size, g_var_size * 2);
			realloc_all_gvariables_array();
		}
		free(find);
		array[0][i] = *add;
	}	
	return (0);
}