#include "shell42.h"
#include "parser.h"

/* A process is a single process.  */
typedef struct  process
{
    struct process *next;       /* next process in pipeline */
    char **argv;                /* for exec */
	char **envp;				/* ADDED BY ME */
    pid_t pid;                  /* process ID */
    char completed;             /* true if process has completed */
    char stopped;               /* true if process has stopped */
    int status;                 /* reported status value */
}   process;

/* A job is a pipeline of processes.  */
typedef struct job
{
    struct job *next;           /* next active job */
    char *command;              /* command line, used for messages */
    process *first_process;     /* list of processes in this job */
    pid_t pgid;                 /* process group ID */
    char notified;              /* true if user told about stopped job */
    struct termios tmodes;      /* saved terminal modes */
    int stdin, stdout, stderr;  /* standard i/o channels */
}   job;


/* REWRITE */
void	launch_process (process *p, pid_t pgid, int stream[3], int foreground)
{
  pid_t pid;

  if (shell_is_interactive)
    {
      /* Put the process into the process group and give the process group
         the terminal, if appropriate.
         This has to be done both by the shell and in the individual
         child processes because of potential race conditions.  */
      pid = getpid ();
      if (pgid == 0) pgid = pid;
      setpgid (pid, pgid);
      if (foreground)
        tcsetpgrp (shell_terminal, pgid);

      /* Set the handling for job control signals back to the default.  */
      signal (SIGINT, SIG_DFL);
      signal (SIGQUIT, SIG_DFL);
      signal (SIGTSTP, SIG_DFL);
      signal (SIGTTIN, SIG_DFL);
      signal (SIGTTOU, SIG_DFL);
      signal (SIGCHLD, SIG_DFL);
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
  execvp (p->argv[0], p->argv);
  perror ("execvp");
  exit (1);
}

/* REWRITE */
void launch_job (job *j, int foreground)
{
	process	*p;
	pid_t	pid;
	int 	mypipe[2]
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
				exit (1);
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
			exit (1);
		}
		else
		{
			/* This is the parent process.  */
			p->pid = pid;
			if (shell_is_interactive)
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
	format_job_info (j, "launched");
	if (!shell_is_interactive)
		wait_for_job (j);
	else if (foreground)
		put_job_in_foreground (j, 0);
	else
		put_job_in_background (j, 0);
}
