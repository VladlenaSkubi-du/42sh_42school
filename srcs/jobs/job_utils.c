/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshawand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:50:07 by hshawand          #+#    #+#             */
/*   Updated: 2020/07/25 15:52:55 by hshawand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "jobs.h"

/*
** Checks if all processes in a given job have either "completed" or "stopped"
** state. Performs user notification about stopped jobs
*/

int		job_is_stopped(job *j, char verbose)
{
	process		*p;
	char		not_completed;

	p = j->first_process;
	not_completed = 0;
	while (p)
	{
		if (!p->completed && !p->stopped)
			return (0);
		!p->completed ? not_completed = 1 : 0;
		p = p->next;
	}
	if (verbose && !j->fg && !j->notified && not_completed)
	{
		ft_printf("[%d] stopped: %s\n", j->jid, j->com);
		j->notified = 1;
	}
	return (1);
}

/*
** Checks if all processes in a given job have "completed" state
*/

int		job_is_completed(job *j)
{
	process		*p;

	p = j->first_process;
	while (p)
	{
		if (!p->completed)
		{
			return (0);
		}
		p = p->next;
	}
	return (1);
}

/*
** Searches and returns particular job node from global job list by pgid
*/

job		*find_job(pid_t pgid)
{
	job *j;

	j = g_first_job;
	while (j)
	{
		if (j->pgid == pgid)
			return (j);
		j = j->next;
	}
	return (NULL);
}

/*
** Removes particular job node from the list and deallocates memory used by it
*/

int		free_job(job *j)
{
	job		*j_last;
	job		*j_next;
	process *temp;

	j_last = g_first_job;
	while (j_last != j && j_last->next && j_last->next != j)
		j_last = j_last->next;
	j_next = j->next;
	j_last->next = j_next;
	if (j == g_first_job)
		g_first_job = j->next;
	while (j->first_process)
	{
		temp = j->first_process;
		j->first_process = j->first_process->next;
		ft_arrdel(temp->argv);
		ft_arrdel(temp->envp);
		free(temp);
	}
	free(j);
	return (0);
}
