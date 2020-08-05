/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:11:39 by hshawand          #+#    #+#             */
/*   Updated: 2020/08/05 14:17:28 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtins_list.h"
#include "jobs.h"
#include "parser.h"

/*
** execvp implementation based on $PATH parsing and execve syscall
*/

int		exec_vp(t_process *p)
{
	if (!(g_path = path_init(p->argv)))
		return (exec_clean(g_path, -1, 0));
	if (execve(g_path, p->argv, p->envp) == -1)
		exit(-1);
	return (0);
}

int		setstream(int src, int dest)
{
	dup2(src, dest);
	close(src);
	return (0);
}

/*
** Executes command using information in the process structure
*/

void	launch_process(t_process *p, pid_t pgid, int stream[3], int foreground)
{
	pid_t	pid;

	if (!p->btin && g_is_interactive)
	{
		pid = getpid();
		if (pgid == 0)
			pgid = pid;
		setpgid(pid, pgid);
		signal(SIGTTOU, SIG_IGN);
		if (foreground)
			tcsetpgrp(STDIN_FILENO, pgid);
		set_proc_sig();
	}
	(stream[0] != STDIN_FILENO) && setstream(stream[0], STDIN_FILENO);
	(stream[1] != STDOUT_FILENO) && setstream(stream[1], STDOUT_FILENO);
	(stream[2] != STDERR_FILENO) && setstream(stream[2], STDERR_FILENO);
	// fd_list_process(entity, 0);
	p->btin ? ft_builtins_check(p, 1) : exec_vp(p);
	exec_clean(g_path, 0, 0);
	!p->btin ? exit(1) : 0;
	std_save(1);
}
