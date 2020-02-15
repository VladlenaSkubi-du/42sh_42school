/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 19:35:23 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/15 20:50:23 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

/*
** Here we come with the counters of the beginning and the end of the 
** final processes and all the fds defined after redirection block
** Flags are defined also before in the parser block. Here we finish the
** preparation by forming the environ array for execution, forming 
** argc and argv variables
*/

int				before_exec(t_ltree *sub)
{
	char		*add = NULL;
	
	sub->envir = init_exec_environ();
	add_local_exec_environ(&sub->envir, add);
	//&sub->args_v
	//&sub->args_c
	return (0);
}

char			**init_exec_environ(void)
{
	char		**envir;
	size_t		i;

	envir = (char**)ft_xmalloc(sizeof(char*) * ENV_BUFFER);
	i = 0;
	while(g_env[i])
	{
		envir[i] = ft_strdup(g_env[i]);
		i++;
	}
	return (envir);
}

int				add_local_exec_environ(char ***envir_exec, char *add)
{
	char		**envir;
	size_t		i;

	envir = *envir_exec;
	i = 0;
	while (envir[i])
		i++;
	if (i >= ENV_BUFFER - 1)
	{
		ft_putendl_fd("It is impossible to allocate so much memory",
			STDOUT_FILENO);
		exit(MALLOC_ERROR);
	}
	envir[i] = ft_strdup(add);
	return (0);
}