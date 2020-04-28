/*
** So, it will be something like execvp
*/

#include "shell42.h"
#include "builtins_list.h"
#include "jobs.h"

int		exec_vp(process *p)
{
	if (!(g_path = path_init(p->argv)))
		return (exec_clean(g_path, -1, 0));

	if (execve(g_path, p->argv, p->envp) == -1) //TODO испрвить на все виды очисток
		exit(-1);
	return (0);
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

int		setstream(int src, int dest)
{
	dup2(src, dest);
	close(dest);
	return (0);
}

void	launch_process (process *p, pid_t pgid, int stream[3], int foreground)
{
	pid_t pid;

 	if (g_is_interactive)
	{
		pid = getpid ();
		if (pgid == 0) pgid = pid;
		setpgid (pid, pgid);
		signal(SIGTTOU, SIG_IGN);
		if (foreground)
			tcsetpgrp(STDIN_FILENO, pgid);
		set_proc_sig();
	}
	(stream[0] != STDIN_FILENO) && setstream(stream[0], STDIN_FILENO);
	(stream[1] != STDOUT_FILENO) && setstream(stream[1], STDOUT_FILENO);
	(stream[2] != STDERR_FILENO) && setstream(stream[2], STDERR_FILENO);
	exec_vp(p);
	exec_clean(g_path, 0, 0);
	exit(1);
}
