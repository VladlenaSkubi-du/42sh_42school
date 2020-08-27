/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 16:03:04 by hshawand          #+#    #+#             */
/*   Updated: 2020/08/27 21:41:59 by rbednar          ###   ########.fr       */
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
	int			child_pid;
	int			status;
	t_job		*j;
	t_process	*proc;

	while ((child_pid = waitpid(-1, &status, WUNTRACED | WNOHANG)) > 0)
	{
		j = g_first_job;
		while (j)
		{
			proc = j->first_process;
			while (proc)
			{
				proc->pid == child_pid ?
				(j->signal = process_update(proc, status)) : 0;
				proc = proc->next;
			}
			j = j->next;
		}
	}
	signal(sig, child_handler);
}

void	set_proc_sig(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
}

/*
** Star Wars reference. Terminates every active process in job. Called from
** free_job. Have to be silent in case of kill(2) failure
*/

void	order_sixty_six(t_job *j)
{
	t_process	*p_iter;

	p_iter = j->first_process;
	while (p_iter)
	{
		if (!p_iter->completed && !p_iter->btin)
			kill(p_iter->pid, SIGKILL);
		p_iter = p_iter->next;
	}
}
