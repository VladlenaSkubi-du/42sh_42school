#include "shell42.h"
#include "jobs.h"

/* Notify the user about stopped or terminated jobs.
   Delete terminated jobs from the active job list.  */

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

void	do_job_notification (void)
{
	job *j, *jlast, *jnext;

	/* Update status information for child processes. Not needed ? */
//	update_status ();

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
		else if (job_is_stopped (j) && !j->notified)
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

process *find_process(job *j, pid_t child_pid)
{
	process *proc;

	proc = j->first_process;
	while (proc && proc->pid != child_pid)
		proc = proc->next;
	return (proc);
}

int		job_is_stopped(job *j)
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
	printf("All stopped\n");
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
	printf("All completed\n");
	return (1);
}

job		*find_job (pid_t pgid)
{
 	job *j;

	j = g_first_job;
	while (j)
	{
		printf("PGID: %d FIND: %d\n", j->pgid, pgid);
		if (j->pgid == pgid)
			return (j);
		j = j->next;
	}
	return (NULL);
}

void	process_update(process *p, int status)
{
	WIFSTOPPED(status) ? (p->stopped = 1) : (p->completed = 1);
	p->status = status;
}

/* Call this handler in case SIGCHLD is raised */
void	child_handler(int sig)
{
	int		child_pid;
	int		status;
	job		*j;
	job		*temp;
	process	*proc;

	while ((child_pid = waitpid(-1, &status, WUNTRACED|WNOHANG)) > 0)
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
			!j->fg && job_is_completed(j) && (temp = j); /* ???  CHECK FOR LEAKS */
			j = j->next;
			temp && free_job(temp); /* CHANGE */
		}
	}
	signal(SIGCHLD, child_handler);
}

/* REWRITE */

int		parent(process	*p, job *j, pid_t pid)
{
	p->pid = pid;
	if (g_is_interactive)
	{
		if (!j->pgid)
			j->pgid = pid;
		setpgid (pid, j->pgid);
	}
	return (0);
}

int		bg_fg_wait(job *j)
{
	if (!g_is_interactive)
		wait_for_job (j);
	else if (j->fg)
		put_job_in_foreground (j, 0);
	else
		put_job_in_background (j, 0);
	return (0);
}

int		fork_job(process *p, job *j, int *infl, int *outfl)
{
	pid_t	pid;
	int 	mypipe[2];

	if (p->next)
	{
		if (pipe (mypipe) < 0)
			return (-1);
		*outfl = mypipe[1];
	}
	else
		*outfl = j->stdout;
	pid = fork ();
	if (pid == 0)
		launch_process(p, j->pgid, (int[3]){*infl, *outfl, j->stderr}, j->fg);
	else if (pid < 0)
		return (-1);
	else
		parent(p, j, pid);
	if (*infl != STDIN_FILENO)
		close (*infl);
	if (*outfl != STDOUT_FILENO)
		close (*outfl);
	*infl = mypipe[0];
	return (0);
}

/* REWRITE */
int	 launch_job (job *j)
{
	process	*p;
	int		infile;
	int		outfile;

	infile = STDIN_FILENO;
	p = j->first_process;
	while (p)
	{
		if (fork_job(p, j, &infile, &outfile) == -1)
			return (-1);
		p = p->next;
	}
//	format_job_info (j, "launched");
	bg_fg_wait(j);
	return (0);
}
