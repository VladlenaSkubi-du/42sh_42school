#include "shell42.h"
#include "builtin42.h"
#include "jobs.h"

int		id_check(t_ltree *pos)
{
	int		i;

	i = 1;
	while (i < pos->ar_c)
	{
		if (pos->ar_v[i][0] == '%')
			return (1);
		i++;
	}
	return (0);
}

int		print_by_id(t_ltree *pos, int options)
{
	int		i;
	job		*job_iter;
	int		id;

	i = 1;
	while (i < pos->ar_c)
	{
		if (pos->ar_v[i][0] == '%')
		{
			id = ft_atoi((pos->ar_v)[i] + 1);
			job_iter = g_first_job;
			while (job_iter && job_iter->jid != id)
				job_iter = job_iter->next;
			is_btin_only(job_iter) ? job_iter = 0 : 0; /* Take from bg_fg_btin.c */
			job_iter ? print_job_info(job_iter, options) :
				error_handler(VARIABLE_ERROR | (ERR_JOB_NF << 9), pos->ar_v[i]);
		}
		i++;
	}
	return (0);
}
