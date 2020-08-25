/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 20:45:28 by hshawand          #+#    #+#             */
/*   Updated: 2020/08/21 22:32:07 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

/*
** Delete pipe process and simplify, leaving only dealing with EXECPATH
*/

int		std_save(int mode)
{
	static int	save[3];

	if (!mode)
	{
		save[0] = dup(STDIN_FILENO);
		save[1] = dup(STDOUT_FILENO);
		save[2] = dup(STDERR_FILENO);
	}
	else
	{
		dup2(save[0], STDIN_FILENO);
		close(save[0]);
		dup2(save[1], STDOUT_FILENO);
		close(save[1]);
		dup2(save[2], STDERR_FILENO);
		close(save[2]);
	}
	return (0);
}

/*int		fork_and_exec(t_ltree *pos, char *path, pid_t *child_pid)
{
	*child_pid = fork();
	if (!*child_pid)
	{
		if (execve(path, pos->ar_v, pos->envir) == -1)
			exit(-1);
	}
	else if (*child_pid < 0)
		return (exec_clean(path, -1, "e-bash: Fork failed"));
	wait(child_pid);
	return (0);
}*/
