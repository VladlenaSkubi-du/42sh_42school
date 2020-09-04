/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_id_btin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshawand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 21:09:15 by hshawand          #+#    #+#             */
/*   Updated: 2020/08/21 21:10:05 by hshawand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"
#include "jobs.h"

int		id_check(int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '%')
			return (1);
		i++;
	}
	return (0);
}

int		print_by_id(int argc, char **argv, int options)
{
	int		i;
	t_job	*job_iter;
	int		id;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '%')
		{
			id = ft_atoi(argv[i] + 1);
			job_iter = g_first_job;
			while (job_iter && job_iter->jid != id)
				job_iter = job_iter->next;
			is_btin_only(job_iter) ? job_iter = 0 : 0;
			job_iter ? print_job_info(job_iter, options) :
				error_handler(VARIABLE_ERROR | (ERR_JOB_NF << 9), argv[i]);
		}
		i++;
	}
	return (0);
}
