#include "shell42.h"
#include "builtin42.h"
#include "jobs.h"

int		is_btin_only(job *j)
{
	process *p_iter;

	p_iter = j->first_process;
	if (!p_iter)
		return (0);
	while (p_iter)
	{
		if (!p_iter->btin)
			return (0);
		p_iter = p_iter->next;
	}
	return (1);
}

int		back_to_life(job *j)
{
	process *p_iter;

	ft_putendl(j->com);
	p_iter = j->first_process;
	while (p_iter)
	{
		if (p_iter->stopped)
			p_iter->stopped = 0;
		p_iter = p_iter->next;
	}
	return (0);
}

int		btin_bg(t_ltree *pos)
{
	job		*job_iter;
	int		id;

	job_iter = g_first_job;
	if (!job_iter) /* No jobs */
		return (error_handler(VARIABLE_ERROR | (ERR_JOB_NF << 9), "current"));
	if (pos->ar_c < 2) /* Empty fg case */
		while (job_iter->next && !is_btin_only(job_iter->next))
			job_iter = job_iter->next;
	else if (pos->ar_v[1][0] == '%')
	{
		id = ft_atoi((pos->ar_v)[1] + 1);
		while (job_iter && job_iter->jid != id)
			job_iter = job_iter->next;
		if (!job_iter)
			return (error_handler(VARIABLE_ERROR | (ERR_JOB_NF << 9), pos->ar_v[1]));
	}
	else
		return (error_handler(VARIABLE_ERROR | (ERR_JOB_NF << 9), pos->ar_v[1]));
	if (is_btin_only(job_iter))
		return (error_handler(VARIABLE_ERROR | (ERR_JOB_NF << 9), "current"));
	back_to_life(job_iter);
	put_job_in_background(job_iter, 1);
	return (0);
}

int		btin_fg(t_ltree *pos)
{
	job		*job_iter;
	int		id;

	job_iter = g_first_job;
	if (!job_iter) /* No jobs */
		return (error_handler(VARIABLE_ERROR | (ERR_JOB_NF << 9), "current"));
	if (pos->ar_c < 2) /* Empty fg case */
		while (job_iter->next && !is_btin_only(job_iter->next))
			job_iter = job_iter->next;
	else if (pos->ar_v[1][0] == '%')
	{
		id = ft_atoi((pos->ar_v)[1] + 1);
		while (job_iter && job_iter->jid != id)
			job_iter = job_iter->next;
		if (!job_iter)
			return (error_handler(VARIABLE_ERROR | (ERR_JOB_NF << 9), pos->ar_v[1]));
	}
	else
		return (error_handler(VARIABLE_ERROR | (ERR_JOB_NF << 9), pos->ar_v[1]));
	if (is_btin_only(job_iter))
		return (error_handler(VARIABLE_ERROR | (ERR_JOB_NF << 9), "current"));
	back_to_life(job_iter);
	put_job_in_foreground(job_iter, 1);
	return (0);
}
