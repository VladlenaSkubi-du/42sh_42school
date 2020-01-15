/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 15:54:55 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/15 21:35:18 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

int		options(int argc, char **argv)
{
	if (argc == 2 && ft_strcmp(argv[1], "--readline") == 0)
	{
		print_help(2);
		return (0);
	}
	if (argc == 2 && ft_strcmp(argv[1], "--simple") == 0)
	{
		print_help(3);
		return (0);
	}
	if (argc == 2 && ft_strcmp(argv[1], "-c") == 0)
	{
		ft_putendl_fd("42sh: -c: option requires an argument", 2); //make error
		return (2);
	}
	return (1);
}

static int		parser(char *line)
{
	ft_putendl_fd(line, 1);
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
		cmd = ft_strdup(argv[2]);
		if (parser(cmd))
			return (-1);
		return (1);
	}
	return (0);
}

int				main(int argc, char **argv)
{
	int			tmp;
	
	save_environment();
	save_shell_variables();
	if ((tmp = options(argc, argv)) != 1)
		return (tmp);
	if ((tmp = noninteractive_shell(argc, argv)) == -1)
		return (1);
	else if (tmp)
		return (0);
	if (interactive_shell('m', EOF, NULL))
		return (1);
	clean_everything();
	return (0);
}

//stopped with signals for readline
