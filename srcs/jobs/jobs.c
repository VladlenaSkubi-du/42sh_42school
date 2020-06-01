#include "shell42.h"
#include "jobs.h"

process *find_process(job *j, pid_t child_pid)
{
	process *proc;

	proc = j->first_process;
	while (proc && proc->pid != child_pid)
		proc = proc->next;
	return (proc);
}

void	process_update(process *p, int status)
{
	WIFSTOPPED(status) && (p->stopped = 1);
	WIFEXITED(status) && (p->completed = 1);
	p->status = status;
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

int		fork_job(process *p, job *j, int *infl, int *outfl)
{
	pid_t	pid;
	int 	mypipe[2];

	if (p->next)
	{
		if (pipe(mypipe) < 0)
			return (-1);
		*outfl = mypipe[1];
	}
	else
		*outfl = j->stdout;
	pid = fork();
	if (pid == 0)
		launch_process(p, j->pgid, (int[3]){*infl, *outfl, j->stderr}, j->fg);
	else if (pid < 0)
		return (-1);
	else
		parent(p, j, pid);
	if (*infl != STDIN_FILENO)
		close(*infl);
	if (*outfl != STDOUT_FILENO)
		close(*outfl);
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
	j->clean = j->fg ? 0 : 1;
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
