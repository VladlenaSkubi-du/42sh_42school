#include "shell42.h"
#include "builtin42.h"
#include "jobs.h"

int		get_status(job	*j, char *buff, int options)
{
	process		*p_iter;
	int			signum;

	ft_bzero(buff, 100);
	if (job_is_stopped(j, 0))
	{
		p_iter = j->first_process;
		while (p_iter && !(p_iter->stopped))
			p_iter = p_iter->next;
		if (!p_iter)
			return (-1);
		signum = WSTOPSIG(p_iter->status);
		if (signum == SIGTTIN && options == 2)
			ft_strcpy(buff, "stopped (tty input) ");
		else if (signum == SIGTTOU && options == 2)
			ft_strcpy(buff, "stopped (tty output)");
		else
			ft_strcpy(buff, "stopped             ");
	}
	else
			ft_strcpy(buff, "runnindg            "); //проверить
	return (0);
}

int		print_job_info(job * j, int options)
{
	char	def;
	char	status[100];

	if (!j->next)
		def = '+';
	else if (!j->next->next)
		def = '-';
	else
		def = ' ';
	if (get_status(j, status, options))
		return (-1);
	options != 1 && ft_printf("[%d]%c ", j->jid, def);
	ft_printf("%d", j->pgid);
	options != 1 && ft_printf(" %s %s", status, j->com);
	ft_printf("\n");
	return (0);
}

int		options_parse(t_ltree *pos)
{
	int		ret;
	int		i;
	int		j;

	i = 1;
	ret = 0;
	while (i < pos->ar_c && pos->ar_v[i][0] == '-')
	{
		j = 1;
		while (pos->ar_v[i][j])
		{
			if (pos->ar_v[i][j] == 'p')
				ret = 1;
			else if (pos->ar_v[i][j] == 'l')
				ret = 2;
			else
				return (-1);
			j++;
		}
		i++;
	}
	return (ret);
}

int		btin_jobs(t_ltree *pos)
{
	job		*job_iter;
	int		options;
	int		id_chk;
	int		error;

	job_iter = g_first_job;
	if (!job_iter || is_btin_only(job_iter)) /* Take from bg_fg_btin.c */
		return (0);
	options = options_parse(pos);
	if (options == -1)
	{
		error = OPTIONS_REQUIRED | ERR_BTIN_INVALID << 9;
		return (options_errors(error, "jobs")); /* Invalid option case */
	}
	id_chk = id_check(pos);
	while (!id_chk && job_iter)
	{
		!is_btin_only(job_iter) ? print_job_info(job_iter, options) : 0; /* Take from bg_fg_btin.c */
		job_iter = job_iter->next;
	}
	id_chk && print_by_id(pos, options);
	return (0);
}
