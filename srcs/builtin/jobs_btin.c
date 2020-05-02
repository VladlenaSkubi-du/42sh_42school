#include "shell42.h"
#include "builtin42.h"
#include "jobs.h"

int		get_status(job	*j, char *buff)
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
		if (signum == SIGTTIN)
			ft_strcpy(buff, "stopped (tty input) ");
		else if (signum == SIGTTOU)
			ft_strcpy(buff, "stopped (tty output)");
		else
			ft_strcpy(buff, "stopped             ");
	}
	else
			ft_strcpy(buff, "runnindg            ");
	return (0);
}

int		print_job_info(job * j)
{
	char	def;
	char	status[100];

	if (!j->next)
		def = '+';
	else if (!j->next->next)
		def = '-';
	else
		def = ' ';
	if (get_status(j, status))
		return (-1);
	printf("[%d]%c %d %s %s\n", j->jid, def, j->pgid, status, j->com);
	return (0);
}

int		btin_jobs(t_ltree *pos) /* TODO: PROCESS OPTIONS! */
{
	job		*job_iter;

	job_iter = g_first_job;
	if (!job_iter)
		return (0);
	while (job_iter)
	{
		print_job_info(job_iter);
		job_iter = job_iter->next;
	}
	return (0);
}
