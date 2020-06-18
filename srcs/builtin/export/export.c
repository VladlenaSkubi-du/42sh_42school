#include <shell42.h>
#include <builtin42.h>

int			ft_add_el(char *arg)
{
	int		i;

	i = 0;
	while (g_envi[i])
		i++;
	if (i == g_var_size || i + 1 == g_var_size)
	{
		g_envi = ft_realloc_array(&g_envi, g_var_size, g_var_size * 2);
		g_var_size = g_var_size * 2;
	}
	g_envi[i] = (char *)ft_xmalloc(ft_strlen(arg) + 2);
	ft_strcpy(g_envi[i] + 1, arg);
	g_envi[i][0] |= ENV_VIS;
	g_envi[i][0] |= SET_VIS;
	return (0);
}

int			change_or_add(char *arg)
{
	int		i;
	int		j;
	char	*tmp;
	char	*error;

	i = 0;
	while (arg[i] != '=')
		i++;
	tmp = ft_strndup(arg, i);
	if ((i = find_in_variable(&j, tmp)) >= 0) //add readonly
	{
		if (g_envi[i][0] && (g_envi[i][0] & READONLY))
		{
			error = ft_strjoin("export: ", tmp);
			error_handler(VARIABLE_ERROR | (ERR_RDONLY << 9), error);
			g_envi[i][0] |= ENV_VIS;
			free(tmp);
			return (0);
		}
		free(g_envi[i]);
		g_envi[i] = (char *)ft_xmalloc(ft_strlen(arg) + 2);
		ft_strcpy(g_envi[i] + 1, arg);
		g_envi[i][0] |= ENV_VIS;
		g_envi[i][0] |= SET_VIS;
	}
	else
		ft_add_el(arg);
	free(tmp);
	return (0);
}

int			do_vis(char *arg)
{
	int		i;
	int		j;

	if ((i = find_in_variable(&j, arg)) < 0)
		return (1);
	g_envi[i][0] |= ENV_VIS;
	g_envi[i][0] |= SET_VIS;
	return (0);
}

int			export_add_vis(t_ltree *pos)
{
	int		i;

	i = 0;
	while (pos->ar_v[++i])
	{
		if (pos->ar_v[i][0] == '-')
			continue ;
		if (ft_strrchr(pos->ar_v[i], '='))
			change_or_add(pos->ar_v[i]);
		else
			do_vis(pos->ar_v[i]);
	}
	return (0);
}

int			export_p(t_ltree *pos)
{
	int		i;
	char	*j;

	i = 0;
	while (g_envi[i])
	{
		if (g_envi[i][0] && (g_envi[i][0] & ENV_VIS))
		{
			j = ft_strchr(g_envi[i] + 1, '=');
			ft_printf("export %.*s", j - (g_envi[i] + 1), g_envi[i] + 1);
			if (j && j + 1)
				ft_printf("=\"%s\"\n", j + 1);
			else
				ft_putchar('\n');
		}
		i++;
	}
	return (0);
}

int			btin_export(t_ltree *pos)
{
	int		flags;

	flags = find_options(1, (char*[]){"p"}, pos->ar_v);
	if (pos->ar_c == 1 || flags == 1)
		return (export_p(pos));
	else
		return (export_add_vis(pos));
	return (0);
}
