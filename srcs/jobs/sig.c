/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshawand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 16:03:04 by hshawand          #+#    #+#             */
/*   Updated: 2020/07/25 16:03:19 by hshawand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "jobs.h"

/*
** Async job control. Updates information according to returned status and per-
** forms cleanup if it is allowed
*/

void	child_handler(int sig)
{
	int		child_pid;
	int		status;
	job		*j;
	job		*temp;
	process	*proc;

	while ((child_pid = waitpid(-1, &status, WUNTRACED | WNOHANG)) > 0)
	{
		j = g_first_job;
		while (j)
		{
			temp = NULL;
			proc = j->first_process;
			while (proc)
			{
				proc->pid == child_pid ? process_update(proc, status) : 0;
				proc = proc->next;
			}
			j->clean && job_is_completed(j) && (temp = j);
			job_is_stopped(j, 1);
			j = j->next;
			temp && free_job(temp);
		}
	}
	signal(SIGCHLD, child_handler);
}

void	set_proc_sig(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
}
