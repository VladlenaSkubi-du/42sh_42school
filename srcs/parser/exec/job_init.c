#include "shell42.h"
#include "jobs.h"

job		*job_new(void)
{
	job		*job_new;
	job		*job_iter;

	job_new = (job *)ft_xmalloc(sizeof(job));
	job_new->first_process = NULL;
	job_new->stdin = STDIN_FILENO;
	job_new->stdout = STDOUT_FILENO;
	job_new->stderr = STDERR_FILENO;
	if (!g_first_job)
		g_first_job = job_new;
	else
	{
		job_iter = g_first_job;
		while (job_iter->next)
			job_iter = job_iter->next;
		job_iter->next = job_new;
	}
	return (job_new);
}

int		vec_dup(char ***dst, char **src)
{
	size_t	i;

	i = 0;
	if (!src)
		return (-1);
	while (src[i])
		i++;
	*dst = (char **)ft_xmalloc(sizeof(char *) * (i + 1));
	while (i > 0)
	{
		i--;
		(*dst)[i] = ft_strdup(src[i]);
	}
	return (0);
}

/* Do we need to copy argv and envp? */

int		process_fill(process *proc, t_ltree *entity)
{
	vec_dup(&proc->argv, entity->ar_v);
	vec_dup(&proc->envp, entity->envir);
	proc->next = NULL;
	return (0);
}

int		process_new(job *jobs, t_ltree *entity)
{
	process	*process_new;
	process	*process_iter;

	if (!entity || !jobs)
		return (-1);
	process_new = (process *)ft_xmalloc(sizeof(process));
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
//	int			foreground;
	int			ret;
	size_t   	li;
	size_t   	sy;
	job			*job;

	ret = 0;

	signal(SIGCHLD, child_handler);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	g_shell_tmodes = g_backup_tty;
	li = find_in_variables(g_rdovar, &sy, "42SH_NONINTERACTIVE=");
	g_is_interactive = !(g_rdovar[li][sy] - '0');
	g_shell_pgid = getpgid(0);
	/* If first entity in pipeline or no jobs yet, form new job */
	if (((entity->flags & PIPED_OUT) && (entity->flags & ~PIPED_IN)) || !g_first_job)
	{
		if(!(job = job_new()))
			ret++;
	}

	/* Create new process in job */
	ret += process_new(job, entity);

	/* If we are done filling job, launch and clean */
	if (!(entity->flags & PIPED_OUT))
	{
		job->fg = !(entity->flags & IS_BG);
		ret += launch_job(job);
	}
	printf("Job done\n");
	return (ret);
}
