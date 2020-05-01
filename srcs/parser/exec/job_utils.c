#include "shell42.h"
#include "jobs.h"

int		job_is_stopped(job *j, char verbose)
{
	process		*p;

	p = j->first_process;
	while (p)
	{
		if (!p->completed && !p->stopped)
		{
//			printf("%s not stopped\n", *(p->argv));
			return (0);
		}
		p = p->next;
	}
	if (verbose && !j->fg && !j->notified)
	{
		ft_printf("[%d] stopped: %s\n", j->jid, j->com);
		j->notified = 1;
	}
	return (1);
}

int		job_is_completed(job *j)
{
	process		*p;

	p = j->first_process;
	while (p)
	{
		if (!p->completed)
		{
//			printf("%s not completed\n", *(p->argv));
			return (0);
		}
		p = p->next;
	}
	return (1);
}

job		*find_job (pid_t pgid)
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

int		free_job(job *j)
{
	job		*j_last;
	job		*j_next;
	process *temp;

	j_last = g_first_job;
	while (j_last->next && j_last->next != j)
		j_last = j_last->next;
	j_next = j->next;

	j_last->next = j_next;

	if (j == g_first_job)
		g_first_job = NULL;

	while (j->first_process)
	{
		temp = j->first_process;
		j->first_process = j->first_process->next;
		free_vec(temp->argv);
		free_vec(temp->envp);
		free(temp);
	}
	free(j);
	return (0);
}

/* Notify the user about stopped or terminated jobs.
   Delete terminated jobs from the active job list.  */

/* TODO: THIS */

void	do_job_notification (void)
{
	job *j, *jlast, *jnext;

	jlast = NULL;
	for (j = g_first_job; j; j = jnext)
	{
		jnext = j->next;

		/* If all processes have completed, tell the user the job has
		completed and delete it from the list of active jobs.  */
		if (job_is_completed (j))
		{
	//		format_job_info (j, "completed");
			if (jlast)
				jlast->next = jnext;
			else
				g_first_job = jnext;
			free_job (j);
		}

		/* Notify the user about stopped jobs,
		marking them so that we won’t do this more than once.  */
		else if (job_is_stopped (j, 0) && !j->notified)
		{
	//		format_job_info (j, "stopped");
			j->notified = 1;
			jlast = j;
		}

      /* Don’t say anything about jobs that are still running.  */
	  	else
			jlast = j;
	}
}
