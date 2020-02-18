/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 15:54:55 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/18 16:46:34 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

int				options(int argc, char **argv)
{
	if (argc == 2 && ft_strcmp(argv[1], "--readline") == 0)
	{
		print_help(2);
		exit(SUCCESS);
	}
	if (argc == 2 && ft_strcmp(argv[1], "--simple") == 0)
	{
		print_help(3);
		exit(SUCCESS);
	}
	if (argc == 2 && ft_strcmp(argv[1], "-c") == 0)
	{
		error_handler(OPTIONS_REQUIRED, NULL);
		exit(OPTIONS_REQUIRED);
	}
	return (0);
}

int				noninteractive_shell(int argc, char **argv)
{
	char		*cmd;

	if (argc > 2 && ft_strcmp(argv[1], "-c") == 0)
	{
		cmd = ft_strdup(argv[2]); //TODO строка может быть нулевой
		g_prompt.prompt_func = NULL;
		if (parser(cmd))
			return (-1); //TODO исправить после вынесения exit_status
		return (1);
	}
	return (0);
}

int				main(int argc, char **argv)
{
	int			tmp;

	g_var_size = ENV_BUFFER;
	save_environment_variables(NULL);
	save_shell_variables();
	save_local_variables(NULL);
	options(argc, argv);
	if ((tmp = noninteractive_shell(argc, argv)) == -1)
		return (1);
	else if (tmp == 1)
		return (0);
	g_prompt.prompt_func = main_prompt;
	if (interactive_shell())
		return (1); //TODO исправить после вынесения exit_status
	return (0);
}

//кучу всяких чисток всего и вся по выходу при ошибкахvalgrin