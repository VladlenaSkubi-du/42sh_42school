#include "shell42.h"
#include "jobs.h"

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

void	set_proc_sig(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
}
