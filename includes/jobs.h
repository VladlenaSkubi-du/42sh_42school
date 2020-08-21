
#ifndef JOBS_H
# define JOBS_H

/* A process is a single process.  */
typedef struct  s_process
{
    struct s_process *next;       /* next process in pipeline */
	int	argc;
    char **argv;                /* for exec */
	char **envp;				/* ADDED BY ME */
    pid_t pid;                  /* process ID */
    char completed;             /* true if process has completed */
    char stopped;               /* true if process has stopped */
	char btin;
    int status;                 /* reported status value */
    t_list *fd;                
}   t_process;

/* A job is a pipeline of processes.  */
typedef struct  s_job
{
    struct s_job *next;           /* next active job */
    char *com;	                /* command line, used for messages */
    t_process *first_process;     /* list of processes in this job */
    pid_t pgid;                 /* process group ID */
	int jid;					/* Job id */
    char notified;              /* true if user told about stopped job */
	char fg;
	char clean;
    struct termios tmodes;      /* saved terminal modes */
    int stdin, stdout, stderr;  /* standard i/o channels */
}   t_job;

struct termios		g_shell_tmodes;
char				g_is_interactive;
pid_t				g_shell_pgid;
char				*g_path;
t_job					*g_first_job;

/* TODO: Redistribute functions between files according to norm */

/*
** File job_init.c
*/

int		vec_dup(char ***dst, char **src);
int     job_init(t_ltree *entity);

/*
** File jobs.c
*/

int	 	launch_job (t_job *j);
void	process_update(t_process *p, int status);
t_process *find_process(t_job *j, pid_t child_pid);

/*
** File job_utils.c
*/

int		job_is_stopped(t_job *j, char verbose);
int		job_is_completed(t_job *j);
t_job		*find_job (pid_t pgid);
int		free_job(t_job *j);
void	do_job_notification (void);

/*
** File bg_fg.c
*/

void	wait_for_job (t_job *j);
void	put_job_in_foreground (t_job *j, int cont); /* QUESTIONABLE */
void	put_job_in_background (t_job *j, int cont);
int		bg_fg_wait(t_job *j);

/*
** File sig.c
*/

void	child_handler(int sig);
void	set_proc_sig(void);
void	order_sixty_six(t_job *j);

/*
** File exec_new.c
*/

void	launch_process (t_process *p, pid_t pgid, int stream[3], int foreground);

/*
** ____________________________________________________________________________
*/

/*
** File exec_core.c
*/

int		std_save(int mode);
int		fork_and_exec(t_ltree *pos, char *path, pid_t *child_pid);

int		exec_core(t_ltree *pos);
int		exec_builtin(t_ltree *pos);
int		exec_internal(t_ltree *pos);

/*
** File path_parse.c
*/

char	*path_init(char **exec_av);
char	*path_search(char *name);
char	*locate_file(char *env_path, char *name);
char	*form_path(char *ret, char *env_path, char *name);
char	**path_parse(void);

/*
** File exec_utils.c
*/

int		exec_clean(char *path, int exit_status, char *msg);
int		ft_builtins_check(t_process *p, int flag); //DELETE
int		fd_list_process(t_process *pos, int flag);
int		path_init_errors(char *exec_av);

#endif
