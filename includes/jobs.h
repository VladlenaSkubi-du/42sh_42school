
#ifndef JOBS_H
#define JOBS_H
# include <stdio.h>
# include <sys/types.h>
# include <termios.h>
# include <unistd.h>
# include <signal.h>
# include "libft_42.h"
# include "shell42.h"
# include "parser.h"

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

struct termios		g_shell_tmodes;
char				g_is_interactive;
pid_t				g_shell_pgid;
char				*g_path;
job					*g_first_job = NULL;

/* TODO: Redistribute functions between files according to norm */

void	wait_for_job (job *j);
void	put_job_in_foreground (job *j, int cont);
void	put_job_in_background (job *j, int cont);

int		exec_vp(process *p);
void	launch_process (process *p, pid_t pgid, int stream[3], int foreground);

job		*job_new(void);
int		vec_dup(char **dst, char **src);
int		process_fill(process *proc, t_ltree *entity);
int		process_new(job *jobs, t_ltree *entity);
int     job_init(t_ltree *entity);

void	free_job(job *j);
void	do_job_notification(void);
process *find_process(job *j, pid_t child_pid);
int		job_is_stopped(job *j);
int		job_is_completed(job *j);
job		*find_job (pid_t pgid);
void	process_update(process *p, int status);
void	child_handler(int sig);
int 	launch_job (job *j, int foreground);

#endif
