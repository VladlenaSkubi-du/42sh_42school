/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshawand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:50:07 by hshawand          #+#    #+#             */
/*   Updated: 2020/07/26 16:48:52 by hshawand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "jobs.h"

/*
** Checks if all processes in a given job have either "completed" or "stopped"
** state. Performs user notification about stopped jobs
*/

int		job_is_stopped(t_job *j, char verbose)
{
	t_process	*p;
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

int		job_is_completed(t_job *j)
{
	t_process		*p_iter;

	p_iter = j->first_process;
	while (p_iter)
	{
		if (!p_iter->completed)
			return (0);
		p_iter = p_iter->next;
	}
		return (1);
}

/*
** Searches and returns particular job node from global job list by pgid
*/

t_job	*find_job(pid_t pgid)
{
	t_job *j;

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

int		free_job(t_job *j)
{
	t_job		*j_last;
	t_job		*j_next;
	t_process	*temp;

	//order_sixty_six(j);
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
