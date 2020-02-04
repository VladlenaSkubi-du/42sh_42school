/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment42.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:45:55 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/04 19:16:51 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

#define         	MAXDIR 100

int					save_environment(void)
{
	extern char		**environ;
	size_t			i;
	size_t			num;

	i = 0;
	while (environ[i])
		i++;
	num = i;
	g_env = (char**)ft_xmalloc((num + 1) * (sizeof(char*)));
	g_env[num] = NULL;
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

	if (var == NULL && num == 0)
	{
		g_lovar = (char**)ft_xmalloc((num + 1) * (sizeof(char*)));
		g_lovar[num] = 0;
		return (0);
	}
	num++;
	tmp = (char**)ft_xmalloc((num + 1) * (sizeof(char*)));
	tmp[num] = 0;
	i = 0;
	while (g_lovar[i])
		tmp[i] = g_lovar[i];
	tmp[i] = ft_strdup(var);
	free(g_lovar);
	g_lovar = tmp;

	i = 0;
	while (g_lovar[i])
		printf("%s\n", g_lovar[i]);
	return (0);
}

/*
** If we need to get line and symbol (after '=') from that the value of the
** variable starts, we sent the name, int what array to search and an integer pointer
*/

size_t			find_in_variables(char **arr, size_t *j, char *name)
{
	size_t		i;

	i = 0;
	while (arr[i] && ft_strncmp(arr[i], name,
		(*j = ft_strchri(arr[i], '=') + 1)) != 0)
		i++;
	if (arr[i] == 0 || arr[i] + *j == 0)
		return (0);
	return (i);
}