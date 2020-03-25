/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 15:54:55 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/22 16:11:05 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

int				check_42sh_c_option(int argc, char **argv)
{
	int			i;

	i = 0;
	while (argv[++i])
	{
		if (argv[i][0] == '-' && argv[i][1] == 'c')
		{
			if (!(ft_strcmp(argv[i], "-c") == 0 && argv[i + 1]))
			{
				error_handler(OPTIONS_REQUIRED | (ERR_EBASH_C << 9), argv[0]);
				usage_btin(argv[0]);
				exit(OPTIONS_REQUIRED);
			}
			else
				noninteractive_shell(argc, &argv[i + 1]);
		}
		else if (!(argv[i][0] == '-' && argv[i][1] == '-'))
		{
			error_handler(OPTIONS_REQUIRED | (ERR_EBASH_C << 9), argv[0]);
			usage_btin(argv[0]);
			exit(OPTIONS_REQUIRED);
		}
	}
	return (0);
}

int				check_42sh_options(int argc, char **argv)
{
	int			flags;
	int			mask;
	int			i;

	flags = find_options(OPTIONS_NUM,
		(char*[]){"c", "--version", "--help", "--readline", "--simple"}, argv);
	if (flags < 0)
		exit(OPTIONS_REQUIRED);
	mask = 1;
	mask = mask << SUBOPTION_STARTS;
	i = 0;
	while (i < OPTIONS_NUM)
	{
		if (flags & (mask << i))
			print_help(i + 1);
		i++;
	}
	return (check_42sh_c_option(argc, argv));
}

int				noninteractive_shell(int argc, char **argv)
{
	char		*cmd;
	size_t		li;
	size_t		sy;

	li = find_in_variables(g_rdovar, &sy, "42SH_NONINTERACTIVE");
	g_rdovar[li][sy] = '1';
	cmd = ft_strdup(argv[0]);
	g_prompt.prompt_func = NULL;
	parser(cmd);
	li = find_in_variables(g_rdovar, &sy, "?=");
	exit(ft_atoi(&g_rdovar[li][sy]));
}

int				main(int argc, char **argv)
{
	g_var_size = ENV_BUFFER;
	save_environment_variables();
	save_readonly_variables();
	save_local_variables();
	check_42sh_options(argc, argv);
	save_shell_variables();
	g_prompt.prompt_func = main_prompt;
	if (interactive_shell())
		return (1); //TODO исправить после вынесения exit_status
	return (0);
}

//кучу всяких чисток всего и вся по выходу при ошибках valgrin