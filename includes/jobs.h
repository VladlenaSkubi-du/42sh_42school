
#ifndef JOBS_H
# define JOBS_H

/* A process is a single process.  */
typedef struct  process
{
    struct process *next;       /* next process in pipeline */
	int	argc;
    char **argv;                /* for exec */
	char **envp;				/* ADDED BY ME */
    pid_t pid;                  /* process ID */
    char completed;             /* true if process has completed */
    char stopped;               /* true if process has stopped */
    int status;                 /* reported status value */
}   process;

/* A job is a pipeline of processes.  */
typedef struct  job
{
    struct job *next;           /* next active job */
    char *com;	                /* command line, used for messages */
    process *first_process;     /* list of processes in this job */
    pid_t pgid;                 /* process group ID */
	int jid;					/* Job id */
    char notified;              /* true if user told about stopped job */
	char fg;
	char clean;
    struct termios tmodes;      /* saved terminal modes */
    int stdin, stdout, stderr;  /* standard i/o channels */
}   job;

struct termios		g_shell_tmodes;
char				g_is_interactive;
pid_t				g_shell_pgid;
char				*g_path;
job					*g_first_job;

/* TODO: Redistribute functions between files according to norm */

/*
** File job_init.c
*/

int		vec_dup(char ***dst, char **src);
int     job_init(t_ltree *entity);

/*
** File jobs.c
*/

int	 	launch_job (job *j);
void	process_update(process *p, int status);
process *find_process(job *j, pid_t child_pid);

/*
** File job_utils.c
*/

int		job_is_stopped(job *j, char verbose);
int		job_is_completed(job *j);
job		*find_job (pid_t pgid);
int		free_job(job *j);
void	do_job_notification (void);

/*
** File bg_fg.c
*/

void	wait_for_job (job *j);
void	put_job_in_foreground (job *j, int cont); /* QUESTIONABLE */
void	put_job_in_background (job *j, int cont);
int		bg_fg_wait(job *j);

/*
** File sig.c
*/

void	child_handler(int sig);
void	set_proc_sig(void);

/*
** File exec_new.c
*/

void	launch_process (process *p, pid_t pgid, int stream[3], int foreground);

/*
** ____________________________________________________________________________
*/

/*
** File exec_init.c
*/

int		exec_init(t_ltree *pos);

/*
** File exec_core.c
*/

int		std_save(int mode);
int		exec_core(t_ltree *pos);
int		exec_builtin(t_ltree *pos);
int		exec_internal(t_ltree *pos);

/*
** File path_parse.c
*/

char	*path_init(char **exec_av);

/*
** File exec_utils.c
*/

int		exec_clean(char *path, int exit_status, char *msg);
int		ft_builtins_check(process *p, int flag);
int		fd_list_process(t_ltree *pos, int mode);

#endif
