#include "shell42.h"

int		change_env_value(char *new_val, int i)
{
	char	bit;

	if (g_envi[i] == NULL)
		return (-1);
	bit = g_envi[i][0];
	free(g_envi[i]);
	g_envi[i] = (char *)ft_xmalloc(ft_strlen(new_val) + 2);
	g_envi[i][0] = bit;
	ft_strcpy(g_envi[i] + 1, new_val);
	return (0);
}

int		add_new_env(char *name)
{
	int		i;

	i = 0;
	while (g_envi[i])
		i++;
	if (i >= g_var_size)
	{
		g_envi = ft_realloc_array(&g_envi, g_var_size, g_var_size * 2);
		g_var_size *= 2;
	}
	g_envi[i] = (char *)ft_xmalloc(ft_strlen(name) + 2);
	ft_strcpy(g_envi[i] + 1, name);
	g_envi[i][0] |= SET_VIS;
	return (i);
}

int		form_local_envir(char ***arr, int size)
{
	int		i;
	int		j;
	char	**tmp;

	i = -1;
	j = 0;
	tmp = *arr;
	while (g_envi[++i])
		if (g_envi[i][0] & ENV_VIS)
			j++;
	tmp = ft_realloc_array(arr, size, size + j + 1);	
	i = 0;
	while (g_envi[i])
	{
		if (g_envi[i][0] && (g_envi[i][0] & ENV_VIS))
		{
			tmp[size] = ft_strdup(g_envi[i] + 1);
			size++;
		}
		i++;
	}
	*arr = tmp;
	return (0);
}

int		find_in_variable(int *j, char *name)
{
	int			i;
	int			tmp;
	int			len_name; 

	i = 0;
	len_name = ft_strlen(name);
	while (g_envi[i])
	{
		tmp = ft_strchri(g_envi[i] + 1, '=');
		if (ft_strncmp(g_envi[i] + 1, name, len_name) == 0 && (tmp == len_name))
		{
			*j = tmp + 2;
			return (i);
		}
		i++;
	}
	return (-1);
}

char	*find_env_value(char *str)
{
	int		i;
	int		j;

	i = find_in_variable(&j, str);
	if (i == -1)
		return (NULL);
	return (&g_envi[i][j]);
}
