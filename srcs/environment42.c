/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment42.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:45:55 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/20 14:56:29 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

int					save_environment(void)
{
	extern char		**environ;
	size_t			i;
	size_t			num;

	i = 0;
	num = count_first_env();
	g_env = (char**)ft_xmalloc((num + 1) * (sizeof(char*)));
	g_env[num] = NULL;
	while (environ[i])
	{
		g_env[i] = ft_strdup(environ[i]);
		i++;
	}
	return (0);
}

int					count_first_env(void)
{
	extern char		**environ;
	int				i;

	i = 0;
	while (environ[i])
		i++;
	return (i);
}

//make variables: SHELL42 (==BASH), SHELL42_PID(==BASHPID),
//SHELL42_CMDS(==BASH_CMDS),
//SHELL42_SUBSHELL (==BASH_SUBSHELL) and so on

int					save_shell_variables(void)
{
	size_t			i;
	size_t			num;

	i = 0;
	num = 10;
	g_shvar = (char**)ft_xmalloc((num + 1) * (sizeof(char*)));
	g_shvar[num] = NULL;
	return (0);
}
