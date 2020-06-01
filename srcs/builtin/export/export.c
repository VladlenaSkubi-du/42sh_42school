#include <shell42.h>
#include <builtin42.h>

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
	return (0);
}
