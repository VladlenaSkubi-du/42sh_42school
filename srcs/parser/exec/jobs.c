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
void launch_job (job *j, int foreground)
{
	process *p;
	pid_t pid;
	int mypipe[2], infile, outfile;

	infile = j->stdin;
	for (p = j->first_process; p; p = p->next)
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
		launch_process (p, j->pgid, infile, outfile, j->stderr, foreground);
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
		if (infile != j->stdin)
			close (infile);
		if (outfile != j->stdout)
			close (outfile);
		infile = mypipe[0];
    }

	format_job_info (j, "launched");

	if (!shell_is_interactive)
		wait_for_job (j);
	else if (foreground)
		put_job_in_foreground (j, 0);
	else
		put_job_in_background (j, 0);
}

int		job_new(job **jobs)
{
	job		*job_new;
	job		*job_iter;

	if (!jobs)
		return (-1);
	job_new = (job *)xmalloc(sizeof(job));
	if (!*jobs)
		*jobs = job_new;
	else
	{
		job_iter = *jobs;
		while (job_iter->next)
			job_iter = job_iter->next;
		job_iter->next = job_new;
	}
	return (0);
}

/* Do we need to copy argv and envp? */

int		process_fill(process *proc, t_ltree *entity)
{
	vec_cpy(proc->argv, entity->ar_v);
	vec_cpy(proc->envp, entity->envir);
	return (0);
}

int		process_new(job *jobs, t_ltree *entity)
{
	process	*process_new;
	process	*process_iter;

	if (!entity || !jobs)
		return (-1);
	process_new = (process *)xmalloc(sizeof(process));
	process_fill(process_new, entity);
	if (!jobs->first_process)
		jobs->first_process = process_new;
	else
	{
		process_iter = jobs->first_process;
		while (process_iter->next)
			process_iter = process_iter->next;
		process_iter->next = process_new;
	}
	return (0);
}

int     job_init(t_ltree *entity)
{
	static job	*jobs = NULL;
	int			foreground;
	int			ret;

	ret = 0;

	/* If first entity in pipeline or no jobs yet, form new job */
	if (((entity->flags & PIPED_OUT) && (entity->flags & ~PIPED_IN)) || !jobs)
	{
		ret += job_new(&jobs);
	}

	/* Create new process in job */
	ret += process_new(jobs, entity);
	
	/* If we are done filling job, launch and clean */
	if (!(entity->flags & PIPED_OUT))
	{
		foreground = !(entity->flags & IS_BG);
		ret += job_launch(jobs, foreground);
		ret += job_clean(jobs);
	}
	return (ret);
}