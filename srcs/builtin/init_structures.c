/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 16:42:09 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/24 13:59:11 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"
#include "builtins_list.h"

t_btin_fc			*init_btin_fc(void)
{
	t_btin_fc		*fc;

	fc = (t_btin_fc*)ft_xmalloc(sizeof(t_btin_fc));
	fc->flag = 0;
	fc->editor = NULL;
    fc->first = 0;
	fc->last = 0;
	fc->s_comp = NULL;
	fc->s_cmd = NULL;
	return (fc);
}

int					btin_return_exit_status(void)
{
	int				li;
	int				sy;
	int				status;
	
	li = find_in_variable(&sy, "?");
	status = ft_atoi(&g_envi[li][sy]);
	return (status);
}

int					btin_check_arg_if_cmd_name(char *arg)
{
	int				i;
	int				answer;

	i = 0;
	if (ft_isalnum(arg[i]) || arg[i] == '_' ||
		(arg[i] == '.' && ft_isalnum(arg[i])))
	{
		answer = check_if_aliased(arg);
		if (answer == ARG_ALIAS)
			return (ARG_ALIAS);
		answer = check_if_builtin(arg);
		if (answer == ARG_BUILTIN)
			return (ARG_BUILTIN);
		return (0);
	}
	return (ARG_INVALID);
}

int					check_if_builtin(char *cmd_name)
{
	int				i;

	i = 1;
	while (g_builtins[i])
	{
		if (!ft_strcmp(cmd_name, g_builtins[i]))
			return (ARG_BUILTIN);
		i++;
	}
	return (-1);
}

int					check_posix_option(char *arg, char *options,
						int (f)(char *arg, int error))
{
	int				j;
	int				k;
	int				check;

	j = 0;
	check = 0;
	while (arg[++j])
	{
		k = -1;
		check = 0;
		while (options[++k])
		{
			if (arg[j] == options[k])
			{
				check = 1;
				break ;
			}
		}
		if (check == 0)
			return (f(arg, OPTIONS_REQUIRED));
	}
	return (0);
}