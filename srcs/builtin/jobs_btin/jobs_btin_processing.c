/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_btin_processing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 21:10:14 by hshawand          #+#    #+#             */
/*   Updated: 2020/08/24 16:34:14 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

int					btin_jobs_error_message(char *option, int error)
{
	char			*error_message;

	error_message = ft_strjoin("jobs: ", option);
	if (error == OPTIONS_REQUIRED)
		error_handler(OPTIONS_REQUIRED |
			(ERR_BTIN_INVALID << 9), error_message);
	else
		error_handler(VARIABLE_ERROR | (ERR_JOB_NF << 9), error_message);
	free(error_message);
	return (BTIN_ERROR);
}

int					btin_jobs_check_options(char **argv, int *iter)
{
	int				i;

	i = 0;
	while (argv[++i])
	{
		if (argv[i][0] == '-')
		{
			if (!argv[i][1])
				return (btin_jobs_error_message(argv[i], VARIABLE_ERROR));
			else if (argv[i][1] == 'p')
				return ((check_posix_option(argv[i], "pl",
						btin_jobs_error_message) != 0) ?
					BTIN_ERROR : FLAG_P);
			else if (argv[i][1] == 'l')
				return ((check_posix_option(argv[i], "pl",
					btin_jobs_error_message) != 0) ?
					BTIN_ERROR : FLAG_L);
			else if (argv[i][1] == '-' && !argv[i][2])
			{
				*iter = i;
				return (0);
			}
		}
	}
	return (0);
}
