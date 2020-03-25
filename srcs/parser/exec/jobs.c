#include "shell42.h"
#include "jobs.h"

/* Notify the user about stopped or terminated jobs.
   Delete terminated jobs from the active job list.  */

void	free_job(job *j)
{
	process *temp;

	while (j->first_process)
	{
		temp = j->first_process;
		j->first_process = j->first_process->next;
		free_vec(temp->argv);
		free_vec(temp->envp);
		free(temp);
	}
	free(j);
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
			return (0);
		p = p->next;
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
			return (0);
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

void	process_update(process *p, int status)
{
	(WIFEXITED(status)) && (p->completed = 1);
	(WIFSTOPPED(status)) && (p->stopped = 1);
	p->status = status;
}

/* Call this handler in case SIGCHLD is raised */
void	child_handler(int sig)
{
	int		child_pid;
	int		child_pgid;
	int		status;
	job		*j;
	process	*proc;

	child_pid = waitpid(0, &status, WUNTRACED);
	child_pgid = getpgid(child_pid);
	j = find_job(child_pgid);
	proc = find_process(j, child_pid);
	process_update(proc, status);
	if (job_is_completed(j))
	{
		/* Background handler? */
	}
	signal(SIGCHLD, child_handler);
}

/* REWRITE */


/* REWRITE */
int	 launch_job (job *j, int foreground)
{
	process	*p;
	pid_t	pid;
	int 	mypipe[2];
	int		infile;
	int		outfile;

	infile = STDIN_FILENO;
	p = j->first_process;
	while (p)
	{
		/* Set up pipes, if necessary.  */
		if (p->next)
		{
			if (pipe (mypipe) < 0)
			{
				perror ("pipe");
				return (-1);
			}
				outfile = mypipe[1];
		}
		else
	        outfile = j->stdout;

			/* Fork the child processes.  */
		pid = fork ();
	 	if (pid == 0)
			/* This is the child process.  */
			launch_process (p, j->pgid, (int[3]){infile, outfile, j->stderr}, foreground);
		else if (pid < 0)
		{
			/* The fork failed.  */
			perror ("fork");
			return (-1);
		}
		else
		{
			/* This is the parent process.  */
			p->pid = pid;
			if (g_is_interactive)
			{
				if (!j->pgid)
				j->pgid = pid;
				setpgid (pid, j->pgid);
			}
		}
		/* Clean up after pipes.  */
		if (infile != STDIN_FILENO)
			close (infile);
		if (outfile != STDOUT_FILENO)
			close (outfile);
		infile = mypipe[0];
		p = p->next;
	}
//	format_job_info (j, "launched");
	if (!g_is_interactive)
		wait_for_job (j);
	else if (foreground)
		put_job_in_foreground (j, 0);
	else
		put_job_in_background (j, 0);
	return (0);
}
