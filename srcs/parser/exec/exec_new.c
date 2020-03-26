/*
** So, it will be something like execvp
*/

#include "shell42.h"
#include "builtins_list.h"
#include "jobs.h"

int		exec_vp(process *p)
{
	if (!(g_path = path_init(p->argv)))
		return (exec_clean(g_path, -1));

	if (execve(g_path, p->argv, p->envp) == -1) //TODO испрвить на все виды очисток
		exit(-1);
	return (0);
}

void	launch_process (process *p, pid_t pgid, int stream[3], int foreground)
{
	pid_t pid;

 	if (g_is_interactive)
	{
      /* Put the process into the process group and give the process group
         the terminal, if appropriate.
         This has to be done both by the shell and in the individual
         child processes because of potential race conditions.  */
		 pid = getpid ();
		 if (pgid == 0) pgid = pid;
		 setpgid (pid, pgid);
		 if (foreground)
		 	tcsetpgrp(STDIN_FILENO, pgid);

		/* Set the handling for job control signals back to the default.  */
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		signal(SIGTTIN, SIG_DFL);
		signal(SIGTTOU, SIG_DFL);
		signal(SIGCHLD, SIG_DFL);
	}

  /* Set the standard input/output channels of the new process.  */
	if (stream[0] != STDIN_FILENO)
	{
		dup2 (stream[0], STDIN_FILENO);
		close (stream[0]);
	}
	if (stream[1] != STDOUT_FILENO)
	{
		dup2 (stream[1], STDOUT_FILENO);
		close (stream[1]);
	}
	if (stream[2] != STDERR_FILENO)
	{
		dup2 (stream[2], STDERR_FILENO);
		close (stream[2]);
	}

	/* Exec the new process.  Make sure we exit.  */
	exec_vp(p);
	exec_clean(g_path, 0);
	exit(1);
}
