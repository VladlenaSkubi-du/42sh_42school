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
	WIFSTOPPED(status) ? (p->stopped = 1) : (p->completed = 1);
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
		setpgid(pid, j->pgid);
	}
	return (0);
}

/*
** Forks given process in given job and provides pipe functionality
*/

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
	pid = !p->btin ? fork() : 0;

	if (pid == 0)
		launch_process(p, j->pgid, (int[3]){*infl, *outfl, j->stderr}, j->fg);
	else if (pid < 0)
		return (-1);
	else
		parent(p, j, pid);
	p->btin ? parent(p, j, getpid()): 0;
	if (*infl != STDIN_FILENO)
		close(*infl);
	if (*outfl != STDOUT_FILENO)
		close(*outfl);
	*infl = mypipe[0];
	return (0);
}

/*
** Iterates through process list in given job, gives all necessary information
** to fork function and calls background/foreground processing function
*/

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
