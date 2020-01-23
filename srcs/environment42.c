/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment42.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:45:55 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/23 17:31:00 by sschmele         ###   ########.fr       */
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
	size_t			num;
	char			*tmp;
	size_t			size_tmp;

	num = 5;
	g_shvar = (char**)ft_xmalloc((num + 1) * (sizeof(char*)));
	g_shvar[num] = NULL;
	tmp = ft_itoa(getuid());
	g_shvar[0] = ft_strjoin("UID=", tmp);
	free(tmp);
	tmp = ft_itoa(geteuid());
	g_shvar[1] = ft_strjoin("EUID=", tmp);
	free(tmp);
	size_tmp = 50;
	tmp = (char*)ft_xmalloc(50);
	g_shvar[2] = ft_strjoin("42SH=", getcwd(tmp, size_tmp));
	free(tmp);
	g_shvar[3] = ft_strdup("42SH_SUBSHELL=0");
	tmp = ft_itoa(getppid());
	g_shvar[4] = ft_strjoin("PPID=", tmp);
	free(tmp);
	return (0);
}
