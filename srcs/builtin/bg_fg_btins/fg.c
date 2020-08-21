/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshawand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 21:15:37 by hshawand          #+#    #+#             */
/*   Updated: 2020/08/21 21:16:19 by hshawand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

int		btin_fg(t_process *pos)
{
	int				flags;

	flags = find_options(2, (char*[]){"", "--help"}, pos->argv);
	if (flags == HELP_FLAG)
		return (usage_btin("fg"));
	if (flags < 0)
		return (btin_return_exit_status());
	return (btin_fg_check_options(pos->argc, pos->argv));
}

int		btin_fg_check_options(int argc, char **argv)
{
	int				i;

	i = 0;
	while (argv[++i])
	{
		if (argv[i][0] == '-')
		{
			if (!argv[i][1])
				return (btin_bg_fg_error_message(1, argv[i], VARIABLE_ERROR));
			else if (argv[i][1] == '-' && !argv[i][2])
				return (btin_fg_init(argc - i, &argv[i]));
		}
		else
		{
			argc -= i - 1;
			if (argc >= 2 && !(argv[i][0] == '%'))
				return (btin_bg_fg_error_message(1, argv[i], VARIABLE_ERROR));
			return (btin_fg_init(argc, &argv[i - 1]));
		}
	}
	return (btin_fg_init(argc, &argv[0]));
}
