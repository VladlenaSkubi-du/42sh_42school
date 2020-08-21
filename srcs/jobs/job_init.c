/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:25:17 by hshawand          #+#    #+#             */
/*   Updated: 2020/08/21 21:58:31 by hshawand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "jobs.h"
#include "parser.h"

t_job		*job_new(void)
{
	t_job		*job_new;
	t_job		*job_iter;

	job_new = (t_job *)ft_xmalloc(sizeof(t_job));
	job_new->first_process = NULL;
	job_new->stdin = STDIN_FILENO;
	job_new->stdout = STDOUT_FILENO;
	job_new->stderr = STDERR_FILENO;
	job_new->next = NULL;
	tcgetattr(STDIN_FILENO, &job_new->tmodes);
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

int			vec_dup(char ***dst, char **src)
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

int			process_new(t_job *jobs, t_ltree *entity)
{
	t_process	*process_new;
	t_process	*process_iter;

	if (!entity || !jobs || entity->ar_c < 1)
		return (-1);
	process_new = (t_process *)ft_xmalloc(sizeof(t_process));
	process_new->argc = entity->ar_c;
	vec_dup(&process_new->argv, entity->ar_v);
	vec_dup(&process_new->envp, entity->envir);
	process_new->fd = entity->fd;
	process_new->next = NULL;
	process_new->btin = ft_builtins_check(process_new, 0) == -1 ? 0 : 1;
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

int			set_globals_and_signals(void)
{
	int		li;
	int		sy;

	signal(SIGCHLD, child_handler);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	g_shell_tmodes = g_backup_tty;
	li = find_in_variable(&sy, "42SH_NONINTERACTIVE");
	g_is_interactive = !(g_envi[li][sy] - '0');
	g_shell_pgid = getpgid(0);
	return (0);
}

/*
** Job/exec block entry point. Allocates memory for new jobs/processes and fills
** them with initial information. Manages redirection and pipes. Checks for
** buiktins and launches them. Launches already filled jobs.
*/

int			job_init(t_ltree *entity)
{
	int			ret;
	t_job		*job;

	ret = 0;
	if (!(entity->flags & PIPED_IN))
		std_save(0);
	set_globals_and_signals();
	if (!(entity->flags & (int)PIPED_IN) || !g_first_job)
		!(job = job_new()) ? ret++ : 0;
	else
	{
		job = g_first_job;
		while (job->next)
			job = job->next;
	}
	ret += process_new(job, entity);
	if (!(entity->flags & (int)PIPED_OUT))
	{
		job->fg = !(entity->flags & (int)IS_BG);
		ret += launch_job(job);
	}
	tcsetpgrp((int)STDIN_FILENO, g_shell_pgid);
	return (btin_return_exit_status());
}
