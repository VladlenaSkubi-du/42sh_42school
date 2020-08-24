/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_fg_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 21:16:55 by hshawand          #+#    #+#             */
/*   Updated: 2020/08/24 17:03:26 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"
#include "jobs.h"

int		is_btin_only(t_job *j)
{
	t_process *p_iter;

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

int		back_to_life(t_job *j)
{
	t_process *p_iter;

	ft_putendl_fd(j->com, STDOUT_FILENO);
	p_iter = j->first_process;
	while (p_iter)
	{
		if (p_iter->stopped)
			p_iter->stopped = 0;
		p_iter = p_iter->next;
	}
	return (0);
}

int		btin_bg_init(int argc, char **argv)
{
	t_job		*job_iter;
	int			id;
	int			i;

	job_iter = g_first_job;
	i = 1;
	if (!job_iter)
		return (btin_bg_fg_error_message(2, "current", VARIABLE_ERROR));
	if (argc < 2)
		while (job_iter->next && !is_btin_only(job_iter->next))
			job_iter = job_iter->next;
	else if (argv[i][0] == '%')
	{
		id = ft_atoi(argv[i] + 1);
		while (job_iter && job_iter->jid != id)
			job_iter = job_iter->next;
		if (!job_iter)
			return (btin_bg_fg_error_message(2, argv[i], VARIABLE_ERROR));
	}
	if (is_btin_only(job_iter))
		return (btin_bg_fg_error_message(2, "current", VARIABLE_ERROR));
	back_to_life(job_iter);
	put_job_in_background(job_iter, 1);
	return (0);
}

int		btin_fg_init(int argc, char **argv)
{
	t_job		*job_iter;
	int			id;
	int			i;

	job_iter = g_first_job;
	i = 1;
	if (!job_iter)
		return (btin_bg_fg_error_message(1, "current", VARIABLE_ERROR));
	if (argc < 2)
		while (job_iter->next && !is_btin_only(job_iter->next))
			job_iter = job_iter->next;
	else if (argv[i][0] == '%')
	{
		id = ft_atoi(argv[i] + 1);
		while (job_iter && job_iter->jid != id)
			job_iter = job_iter->next;
		if (!job_iter)
			return (btin_bg_fg_error_message(1, argv[i], VARIABLE_ERROR));
	}
	if (is_btin_only(job_iter))
		return (btin_bg_fg_error_message(1, "current", VARIABLE_ERROR));
	back_to_life(job_iter);
	put_job_in_foreground(job_iter, 1);
	return (0);
}

/*
** @where is 1 for fg and 2 for
*/

int		btin_bg_fg_error_message(int where, char *option, int error)
{
	char			*error_message;

	error_message = ft_strjoin(((where == 1) ? "fg: " : "bg: "), option);
	if (error)
		error_handler(VARIABLE_ERROR | (ERR_JOB_NF << 9), error_message);
	free(error_message);
	return (BTIN_ERROR);
}
