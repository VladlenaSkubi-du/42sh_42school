/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 16:27:36 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/24 14:31:06 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"
#include "jobs.h"

int				btin_exit(t_process *pos)
{
	int			status;
	t_job		*job_iter;

	job_iter = g_first_job;
	while (job_iter)
	{
		if (!job_is_completed(job_iter) && !is_btin_only(job_iter))
		{
			ft_putendl_fd("There are still alive jobs", STDOUT_FILENO);
			return (BTIN_ERROR);
		}
		job_iter = job_iter->next;
	}
	if (pos->argc > 2)
	{
		error_handler(VARIABLE_ERROR | (ERR_TOO_MANY << 9), "exit");
		return (BTIN_ERROR);
	}
	status = 0;
	if (pos->argc > 1 && (status = btin_exit_arguments(pos->argv)) == BTIN_ERROR)
		return (BTIN_ERROR);
	ft_putendl_fd("exit", STDOUT_FILENO);
	fill_hist_in_file();
	clean_everything();
	exit(status);
}

int				btin_exit_error(char *option)
{
	char	*error_message;

	error_message = ft_strjoin("exit: ", option);
	error_handler(SYNTAX_ERROR | (ERR_NUMERIC << 9), error_message);
	usage_btin("exit");
	free(error_message);
	return (BTIN_ERROR);
}

int				btin_exit_arguments(char **ar_v)
{
	int			status;
	int			i;

	status = 0;
	if (ft_strcmp(ar_v[1], "--help") == '0')
		return (usage_btin("exit"));
	i = (ar_v[1][0] && ar_v[1][0] == '-') ? 0 : -1;
	while (ar_v[1][++i])
		if (!(ar_v[1][i] >= '0' && ar_v[1][i] <= '9'))
			return (btin_exit_error(ar_v[1]));
	status = ft_atoi(ar_v[1]);
	(status < 0) ? status &= 0xFF : 0;
	return (status);
}
