/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 17:41:48 by kfalia-f          #+#    #+#             */
/*   Updated: 2020/08/18 21:20:53 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>
#include <builtin42.h>

int			change_or_add(char *arg)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (arg[i] != '=')
		i++;
	tmp = ft_strndup(arg, i);
	if ((i = find_in_variable(&j, tmp)) >= 0)
	{
		if (g_envi[i][0] && (g_envi[i][0] & READONLY))
			return (export_error(&tmp, i));
		change_env_value(arg, i);
		g_envi[i][0] |= ENV_VIS;
	}
	else
	{
		i = add_new_env(arg);
		g_envi[i][0] |= ENV_VIS;
	}
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

int			export_add_vis(char **argv)
{
	int		i;
	char	*new_var;

	i = 0;
	while (argv[++i])
	{
		if (argv[i][0] == '-')
			continue ;
		if (ft_strrchr(argv[i], '='))
		{
			new_var = ft_parsing_str(argv[i]);
			change_or_add(new_var);
			free(new_var);
		}
		else
			do_vis(argv[i]);
	}
	return (0);
}

int			export_p(void)
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

int			btin_export(t_process *pos)
{
	int		flags;

	flags = find_options(2, (char*[]){"p", "--help"}, pos->argv);
	if (flags == HELP_FLAG)
		return (usage_btin("export"));
	else if (flags < 0)
		return (btin_return_exit_status());
	if (pos->argc == 1 || flags == 1)
		return (export_p());
	else
		return (export_add_vis(pos->argv));
	return (0);
}
