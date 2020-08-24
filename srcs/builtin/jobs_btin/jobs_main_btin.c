/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_main_btin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 21:11:39 by hshawand          #+#    #+#             */
/*   Updated: 2020/08/24 16:33:40 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"
#include "jobs.h"

int		get_status(t_job *j, char *buff, int options)
{
	t_process	*p_iter;
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
		ft_strcpy(buff, "runnindg            ");
	return (0);
}

int		print_job_info(t_job *j, int options)
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
	options != FLAG_P && ft_printf("[%d]%c ", j->jid, def);
	ft_printf("%d", j->pgid);
	options != FLAG_P && ft_printf(" %s %s", status, j->com);
	ft_printf("\n");
	return (0);
}

int		btin_jobs_init(int argc, char **argv)
{
	t_job	*job_iter;
	int		options;
	int		id_chk;
	int		iter;

	iter = 0;
	options = btin_jobs_check_options(argv, &iter);
	if (!(options == FLAG_L || options == FLAG_P || options == 0))
		return (BTIN_ERROR);
	if (iter != 0)
		argc -= iter;
	job_iter = g_first_job;
	if (argc >= 2 && (!job_iter || is_btin_only(job_iter)))
		return (btin_jobs_error_message(argv[iter + 1], VARIABLE_ERROR));
	else if (!job_iter || is_btin_only(job_iter))
		return (0);
	id_chk = id_check(argc, &argv[iter]);
	while (!id_chk && job_iter)
	{
		!is_btin_only(job_iter) ? print_job_info(job_iter, options) : 0;
		job_iter = job_iter->next;
	}
	id_chk && print_by_id(argc, &argv[iter], options);
	return (0);
}

int		btin_jobs(t_process *pos)
{
	int				flags;

	flags = find_options(2, (char*[]){"-pl", "--help"}, pos->argv);
	if (flags == HELP_FLAG)
		return (usage_btin("jobs"));
	if (flags < 0)
		return (BTIN_ERROR);
	return (btin_jobs_init(pos->argc, pos->argv));
}
