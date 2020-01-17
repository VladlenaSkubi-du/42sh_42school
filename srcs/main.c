/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 15:54:55 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/17 15:31:20 by sschmele         ###   ########.fr       */
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

static int		parser(char *line)
{
	ft_putendl_fd(line, 1);
	free(line);
	// g_cmd = line;
	// g_cmd_size = ft_strlen(g_cmd);
	// ft_get_techline();
	// nullify();
	// ft_slice();
	return (0);
}

int				noninteractive_shell(int argc, char **argv)
{
	char		*cmd;

	if (argc > 2 && ft_strcmp(argv[1], "-c") == 0)
	{
		cmd = ft_strdup(argv[2]); //TODO строка может быть нулевой
		if (parser(cmd))
			return (-1); //TODO исправить после вынесения exit_status
		return (1);
	}
	return (0);
}

int				main(int argc, char **argv)
{
	int			tmp;

	save_environment();
	save_shell_variables();
	options(argc, argv);
	if ((tmp = noninteractive_shell(argc, argv)) == -1)
		return (1);
	else if (tmp == 1)
		return (0);
	if (interactive_shell('m', 0, NULL))
		return (1); //TODO исправить после вынесения exit_status
	clean_everything();
	return (0);
}

//кучу всяких чисток всего и вся по выходу при ошибках
