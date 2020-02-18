/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment42.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:45:55 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/18 13:54:48 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

int					save_environment(void)
{
	extern char		**environ;
	size_t			i;

	g_env = (char**)ft_xmalloc((g_var_size + 1) * (sizeof(char*)));
	i = 0;
	while (environ[i])
	{
		g_env[i] = ft_strdup(environ[i]);
		i++;
	}
	return (0);
}

// int					count_first_env(void)
// {
// 	extern char		**environ;
// 	int				i;

// 	i = 0;
// 	while (environ[i])
// 		i++;
// 	return (i);
// }

//make variables: SHELL42 (==BASH), SHELL42_PID(==BASHPID),
//SHELL42_CMDS(==BASH_CMDS),
//SHELL42_SUBSHELL (==BASH_SUBSHELL) and so on

int					save_shell_variables(void)
{
	size_t			num;
	char			*tmp;
	size_t			size_tmp;

	num = 9;
	g_shvar = (char**)ft_xmalloc((num + 1) * (sizeof(char*)));
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
	g_shvar[5] = ft_strdup("42SH_PARSER=0");
	save_history_variables();
	return (0);
}

int					save_history_variables(void)
{	
	char			*tmp;

	tmp = define_history_file();
	g_shvar[6] = ft_strjoin("HISTFILE=", tmp);
	free(tmp);
	tmp = ft_itoa(MAX_HISTORY);
	g_shvar[7] = ft_strjoin("HISTFILESIZE=", tmp);
	free(tmp);
	g_shvar[8] = ft_strdup("EDITOR=vim");
	return (0);
}

int					save_local_variables(char *var)
{
	static size_t	num;
	char			**tmp;
	size_t			i;

	if (var == NULL)
	{
		g_lovar = (char**)ft_xmalloc((g_var_size + 1) * (sizeof(char*)));
		return (0);
	}
	tmp[num] = ft_strdup(var);
	num++;
	if (num == g_var_size)
		realloc_all_variables_array();
	return (0);
}

/*
** If we need to get line and symbol (after '=') from that the value of the
** variable starts, we sent the name, int what array to search and an integer pointer
*/

size_t			find_in_variables(char **arr, size_t *j, char *name)
{
	size_t		i;
	size_t		tmp;

	i = 0;
	while (arr[i])
	{
		tmp = ft_strchri(arr[i], '=') + 1;
		if (ft_strncmp(arr[i], name, tmp) == 0 && arr[i][tmp])
		{
			*j = tmp;
			return (i);
		}
		i++;
	}
	return (-1);
}