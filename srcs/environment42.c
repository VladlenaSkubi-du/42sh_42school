/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment42.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:45:55 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/12 22:13:59 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

/*
** Can be changed by assignment or export and added by export-builtin
*/

int					save_environment_variables(char *env_var)
{
	extern char		**environ;
	size_t			num;

	num = 0;
	if (g_env == NULL)
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
		g_env_num = num;
		return (0);
	}
	while (g_env[num])
		num++;
	(num == g_var_size) ? realloc_all_gvariables_array() : 0;
	g_env[num] = ft_strdup(env_var);
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

	num = 9;
	g_rdovar = (char**)ft_xmalloc((num + 1) * (sizeof(char*)));
	g_rdovar[0] = (char*)ft_xmalloc(sizeof(char) * MAX_EXIT_STATUS);
	g_rdovar[0] = ft_strcpy(g_rdovar[0], "?=0");
	tmp = ft_itoa(getuid());
	g_rdovar[1] = ft_strdup("0=e-bash");
	g_rdovar[2] = ft_strjoin("UID=", tmp);
	free(tmp);
	tmp = ft_itoa(geteuid());
	g_rdovar[3] = ft_strjoin("EUID=", tmp);
	free(tmp);
	size_tmp = 50;
	tmp = (char*)ft_xmalloc(50);
	g_rdovar[4] = ft_strjoin("42SH=", getcwd(tmp, size_tmp));
	free(tmp);
	g_rdovar[5] = ft_strdup("42SH_SUBSHELL=0");
	tmp = ft_itoa(getppid());
	g_rdovar[6] = ft_strjoin("PPID=", tmp);
	free(tmp);
	g_rdovar[7] = ft_strdup("42SH_PARSER=0");
	g_rdovar[8] = ft_strdup("42SH_NONINTERACTIVE=0");
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
	size_t			li;
	size_t			co;

	num = 4;
	g_shvar = (char**)ft_xmalloc((num + 1) * (sizeof(char*)));
	li = find_in_variables(g_env, &co, "HOME=");
	tmp = (li >= g_env_num) ? define_history_file() :
		ft_strjoin(&g_env[li][co], "/.42sh_history");
	g_shvar[0] = ft_strjoin("HISTFILE=", tmp);
	free(tmp);
	tmp = ft_itoa(MAX_HISTBUF);
	g_shvar[1] = ft_strjoin("HISTSIZE=", tmp);
	free(tmp);
	tmp = ft_itoa(MAX_HISTFILE);
	g_shvar[2] = ft_strjoin("HISTFILESIZE=", tmp);
	free(tmp);
	g_shvar[3] = ft_strdup("FCEDIT=vim");
	return (0);
}

/*
** Can be changed by assignment and added -
** local variables that exist within a session
*/

int					save_local_variables(char *lovar)
{
	size_t	num;

	if (g_lovar == NULL)
	{
		g_lovar = (char**)ft_xmalloc((g_var_size + 1) * (sizeof(char*)));
		return (0);
	}
	num = 0;
	while (g_lovar[num])
		num++;
	if (num == g_var_size)
		realloc_all_gvariables_array();
	g_lovar[num] = lovar;
	return (0);
}

int                 exit_status_variable(int status)
{
    char            *tmp;

    tmp = ft_itoa(status);
    ft_bzero(&g_rdovar[0][2], MAX_EXIT_STATUS - 2);
   	ft_strcpy(&g_rdovar[0][2], tmp);
    free(tmp);
    return (0);
}
