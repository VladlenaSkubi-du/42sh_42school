#include "shell42.h"
#include "builtin42.h"

int			btin_unset(t_ltree *pos)
{
	size_t	unused;
	int		j;
	size_t	i;

	i = 1;
	while (i < pos->ar_c)
	{
		if ((j = find_in_variables(g_env, &unused, pos->ar_v[i])) != -1)
			unset_from_array(&g_env, j);
		if ((j = find_in_variables(g_lovar, &unused, pos->ar_v[i])) != -1)	
			unset_from_array(&g_lovar, j);
		i++;
	}
	return (0);	
}