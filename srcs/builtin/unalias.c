/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unalias.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 20:31:08 by rbednar           #+#    #+#             */
/*   Updated: 2020/08/27 10:22:03 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

/*
** No arguments as well as 'unalias --' is no-options error command
*/

int		btin_unalias(t_process *pos)
{
	int	flags;

	flags = find_options(2, (char*[]){"a", "--help"}, pos->argv);
	if (flags == HELP_FLAG)
		return (usage_btin("unalias"));
	if (flags < 0)
		return (BTIN_ERROR);
	if (pos->argc < 2)
	{
		usage_btin("unalias");
		return (BTIN_ERROR);
	}
	return (btin_unalias_check_options(pos->argv));
}

int		btin_unalias_check_options(char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		if (argv[i][0] == '-')
		{
			if (!argv[i][1])
				return (btin_unalias_error(argv[i], VARIABLE_ERROR));
			else if (argv[i][1] == 'a')
				return ((check_posix_option(argv[i], "a",
					btin_unalias_error) != 0) ?
					BTIN_ERROR : btin_unalias_clean_commands());
			else if (argv[i][1] == '-' && !argv[i][2])
			{
				if (argv[i + 1])
					return (btin_unalias_init(&argv[++i]));
				usage_btin("unalias");
				return (BTIN_ERROR);
			}
		}
		else
			return (btin_unalias_init(&argv[i]));
	}
	return (0);
}

int		btin_unalias_error(char *option, int error)
{
	char	*error_message;

	error_message = ft_strjoin("unalias: ", option);
	if (error == OPTIONS_REQUIRED)
		error_handler(OPTIONS_REQUIRED | (ERR_BTIN_INVALID << 9),
			error_message);
	else
		error_handler(VARIABLE_ERROR, error_message);
	free(error_message);
	return (BTIN_ERROR);
}

int		btin_unalias_init(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		btin_alias_init(argv, &argv[i], MINUS);
		i++;
	}
	return (0);
}

int		btin_unalias_clean_commands(void)
{
	btin_alias_init(NULL, NULL, DEL_ALL);
	return (0);
}
