#include "shell42.h"
#include "parser.h"

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

int		vec_dup(char **dst, char **src)
{
	char	**temp;
	size_t	i;

	temp = src;
	i = 0
	if (!src)
		return (-1);
	while (src[i])
		i++;
	dst = (char **)xmalloc(sizeof(char *) * (i + 1));
	dst[i] = NULL;
	i--;
	while (i >= 0)
	{
		dst[i] = ft_strdup(src[i]);
		i--;
	}
	return (0);
}

/* Do we need to copy argv and envp? */

int		process_fill(process *proc, t_ltree *entity)
{
	vec_dup(proc->argv, entity->ar_v);
	vec_dup(proc->envp, entity->envir);
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
	}
	return (ret);
}
