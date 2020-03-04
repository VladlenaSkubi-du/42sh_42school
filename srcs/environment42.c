/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment42.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:45:55 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/04 20:17:13 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

/*
** Can be changed by assignment or export and added by export-builtin
*/

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

/*
** Can be read by the user and corrected only within the shell-program
*/

int					save_readonly_variables(void)
{
	size_t			num;
	char			*tmp;
	size_t			size_tmp;

	num = 8;
	g_rdovar = (char**)ft_xmalloc((num + 1) * (sizeof(char*)));
	g_rdovar[0] = (char*)ft_xmalloc(MAX_EXIT_STATUS);
	g_rdovar[0] = ft_strcpy(g_rdovar[0], "?=0");
	tmp = ft_itoa(getuid());
	g_rdovar[1] = ft_strjoin("UID=", tmp);
	free(tmp);
	tmp = ft_itoa(geteuid());
	g_rdovar[2] = ft_strjoin("EUID=", tmp);
	free(tmp);
	size_tmp = 50;
	tmp = (char*)ft_xmalloc(50);
	g_rdovar[3] = ft_strjoin("42SH=", getcwd(tmp, size_tmp));
	free(tmp);
	g_rdovar[4] = ft_strdup("42SH_SUBSHELL=0");
	tmp = ft_itoa(getppid());
	g_rdovar[5] = ft_strjoin("PPID=", tmp);
	free(tmp);
	g_rdovar[6] = ft_strdup("42SH_PARSER=0");
	g_rdovar[7] = ft_strdup("42SH_NONINTERACTIVE=0");
	return (0);
}

/*
** Can be changed by assignment, can NOT be added
** If there is an export variable - is transferred to the g_env
*/

int					save_shell_variables(void)
{
	size_t			num;
	char			*tmp;

	num = 4;
	g_shvar = (char**)ft_xmalloc((num + 1) * (sizeof(char*)));
	tmp = define_history_file();
	g_shvar[0] = ft_strjoin("HISTFILE=", tmp);
	free(tmp);
	tmp = ft_itoa(MAX_HISTORY);
	g_shvar[1] = ft_strjoin("HISTFILESIZE=", tmp);
	free(tmp);
	g_shvar[2] = ft_strdup("FCEDIT=vim");
	return (0);
}

/*
** Can be changed by assignment and added -
** local variables that exist within a session
*/

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

int                 exit_status_variable(int status)
{
    char            *tmp;

    tmp = ft_itoa(status);
    ft_bzero(&g_rdovar[0][2], MAX_EXIT_STATUS - 2);
    g_rdovar[0] = ft_strcpy(&g_rdovar[0][2], tmp);
    free(tmp);
    return (0);
}
