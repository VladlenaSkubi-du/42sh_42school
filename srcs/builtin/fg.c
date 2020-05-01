#include "shell42.h"
#include "builtin42.h"
#include "jobs.h"

int		back_to_life(job *j)
{
	process *p_iter;

	p_iter = j->first_process;
	while (p_iter)
	{
		if (p_iter->stopped)
			p_iter->stopped = 0;
		p_iter = p_iter->next;
	}
	return (0);
}

int		btin_fg(t_ltree *pos)
{
	job		*job_iter;
	int		id;

	job_iter = g_first_job;
	if (!job_iter) /* No jobs */
		return (-1);
	if (pos->ar_c < 2) /* Empty fg case */
	{
		while (job_iter->next)
			job_iter = job_iter->next;
	}
	else
	{
		id = atoi((pos->ar_v)[1]);
		while (job_iter && job_iter->jid != id)
			job_iter = job_iter->next;
		if (!job_iter)
			return (-1); /* Couldn't find job by provided jid */
	}
	ft_putendl(job_iter->com);
	back_to_life(job_iter);
	put_job_in_foreground(job_iter, 1);
	return (0);
}
