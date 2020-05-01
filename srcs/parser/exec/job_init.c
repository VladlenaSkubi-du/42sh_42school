#include "shell42.h"
#include "jobs.h"
#include "parser.h"

job		*job_new(t_ltree *entity)
{
	job		*job_new;
	job		*job_iter;

	job_new = (job *)ft_xmalloc(sizeof(job));
	job_new->first_process = NULL;
	job_new->stdin = STDIN_FILENO;
	job_new->stdout = STDOUT_FILENO;
	job_new->stderr = STDERR_FILENO;
	if (!g_first_job)
	{
		job_new->jid = 1;
		g_first_job = job_new;
	}
	else
	{
		job_iter = g_first_job;
		while (job_iter->next)
			job_iter = job_iter->next;
		job_new->jid = job_iter->jid + 1;
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

int		process_new(job *jobs, t_ltree *entity)
{
	process	*process_new;
	process	*process_iter;

	if (!entity || !jobs || entity->ar_c < 1)
		return (-1);
	process_new = (process *)ft_xmalloc(sizeof(process));
	vec_dup(&process_new->argv, entity->ar_v);
	vec_dup(&process_new->envp, entity->envir);
	process_new->next = NULL;
	if (!jobs->first_process)
	{
		jobs->com = (process_new->argv)[0];
		jobs->first_process = process_new;
	}
	else
	{
		process_iter = jobs->first_process;
		while (process_iter->next)
			process_iter = process_iter->next;
		process_iter->next = process_new;
	}
	return (0);
}

int		set_globals_and_signals(void)
{
	size_t   	li;
	size_t   	sy;

	signal(SIGCHLD, child_handler);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	g_shell_tmodes = g_backup_tty;
	li = find_in_variables(g_rdovar, &sy, "42SH_NONINTERACTIVE=");
	g_is_interactive = !(g_rdovar[li][sy] - '0');
	g_shell_pgid = getpgid(0);
	return (0);
}

int     job_init(t_ltree *entity)
{
	int			ret;
	job			*job;

	ret = 0;
	fd_list_process(entity, 0);
	if (!exec_builtin(entity))
		return (ret);
	set_globals_and_signals();
	if (!(entity->flags & PIPED_IN) || !g_first_job)
		!(job = job_new(entity)) ? ret++ : 0;
	else
	{
		job = g_first_job;
		while (job->next)
			job = job->next;
	}
	ret += process_new(job, entity);
	if (!(entity->flags & PIPED_OUT))
	{
		job->fg = !(entity->flags & IS_BG);
		ret += launch_job(job);
	}
	tcsetpgrp(STDIN_FILENO, g_shell_pgid);
	fd_list_process(entity, 1);
	return (ret);
}
