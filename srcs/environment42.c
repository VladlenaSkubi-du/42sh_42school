/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment42.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:45:55 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/02 20:02:51 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

int					save_environment_variables(char *env_var)
{
	extern char		**environ;
	static size_t	num;

	if (env_var == NULL)
	{
		g_env = (char**)ft_xmalloc((g_var_size + 1) * (sizeof(char*)));
		while (environ[num])
		{
			if (num == g_var_size)
			{
				g_env = ft_realloc_array(&g_env, g_var_size, g_var_size * 2);
				g_var_size *= 2;
			}
			g_env[num] = ft_strdup(environ[num]);
			num++;
		}
		return (0);
	}
	if (num == g_var_size)
		realloc_all_gvariables_array();
	g_env[num] = ft_strdup(env_var);
	num++;
	return (0);
}

//make variables: SHELL42 (==BASH), SHELL42_PID(==BASHPID),
//SHELL42_CMDS(==BASH_CMDS),
//SHELL42_SUBSHELL (==BASH_SUBSHELL) and so on

int					save_shell_variables(void)
{
	size_t			num;
	char			*tmp;
	size_t			size_tmp;

	num = 10;
	g_shvar = (char**)ft_xmalloc((num + 1) * (sizeof(char*)));
	g_shvar[0] = ft_strdup("?=0");
	tmp = ft_itoa(getuid());
	g_shvar[1] = ft_strjoin("UID=", tmp);
	free(tmp);
	tmp = ft_itoa(geteuid());
	g_shvar[2] = ft_strjoin("EUID=", tmp);
	free(tmp);
	size_tmp = 50;
	tmp = (char*)ft_xmalloc(50);
	g_shvar[3] = ft_strjoin("42SH=", getcwd(tmp, size_tmp));
	free(tmp);
	g_shvar[4] = ft_strdup("42SH_SUBSHELL=0");
	tmp = ft_itoa(getppid());
	g_shvar[5] = ft_strjoin("PPID=", tmp);
	free(tmp);
	g_shvar[6] = ft_strdup("42SH_PARSER=0");
	save_history_variables();
	return (0);
}

int					save_history_variables(void)
{	
	char			*tmp;

	tmp = define_history_file();
	g_shvar[7] = ft_strjoin("HISTFILE=", tmp);
	free(tmp);
	tmp = ft_itoa(MAX_HISTORY);
	g_shvar[8] = ft_strjoin("HISTFILESIZE=", tmp);
	free(tmp);
	g_shvar[9] = ft_strdup("EDITOR=vim");
	return (0);
}

int					save_local_variables(char *lovar)
{
	static size_t	num;

	if (lovar == NULL)
	{
		g_lovar = (char**)ft_xmalloc((g_var_size + 1) * (sizeof(char*)));
		return (0);
	}
	if (num == g_var_size)
		realloc_all_gvariables_array();
	g_lovar[num] = ft_strdup(lovar);
	num++;
	return (0);
}
