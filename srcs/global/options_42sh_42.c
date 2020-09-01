/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_42sh_42.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 16:44:53 by sschmele          #+#    #+#             */
/*   Updated: 2020/09/01 21:20:52 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

int				check_shell_options(char **argv)
{
	int			flags;
	int			mask;
	int			i;
	int			tmp;

	flags = find_options(OPTIONS_NUM,
		(char*[]){"c", "--version", "--help", "--readline", "--simple"}, argv);
	if (flags < 0)
		return (btin_shell_error_message(NULL, OPTIONS_REQUIRED));
	mask = 1;
	tmp = 1;
	mask = mask << SUBOPTION_STARTS;
	i = 0;
	while (i < OPTIONS_NUM)
	{
		if (flags & (mask << i))
		{
			print_help(i + 1);
			tmp = 1;
		}
		i++;
	}
	if (tmp)
		return (0);
	return (check_shell_c_option(argv));
}

int				check_shell_c_option(char **argv)
{
	int			i;

	i = 0;
	while (argv[++i])
	{
		if (argv[i][0] == '-')
		{
			if (!argv[i][1])
				return (btin_shell_error_message(argv[i], OPTIONS_REQUIRED));
			else if (argv[i][1] == 'c')
				return ((check_posix_option(argv[i], "c",
						btin_shell_error_message) != 0) ?
					OPTIONS_REQUIRED : noninteractive_shell(&argv[++i]));
		}
		return (check_shell_script_execution(argv[i]));
	}
	return (0);
}

int				btin_shell_error_message(char *option, int error)
{
	char		*error_message;

	error_message = ft_strjoin(find_env_value("0"), ": ");
	error_message = ft_strrejoin(error_message, option);
	if (error == OPTIONS_REQUIRED)
		error_handler(OPTIONS_REQUIRED |
			(ERR_BTIN_ARG << 9), error_message);
	else
		error_handler(VARIABLE_ERROR |
			(ERR_BTIN_INVALID << 9), error_message);
	free(error_message);
	return (error);
}

int				check_shell_script_execution(char *file)
{
	struct stat	stat_buf;
	
	if (access(file, F_OK) == -1)
	{
		error_handler(VARIABLE_ERROR | (ERR_CD_NO_FILE_DIR << 9), file);
		return (VARIABLE_ERROR);
	}
	if (access(file, R_OK) == -1 || stat(file, &stat_buf) != 0
			|| (stat_buf.st_mode & (S_IRUSR | S_IRGRP | S_IROTH)) == 0)
	{
		error_handler(COMMAND_NON_EXECUTABLE | (ERR_NO_ACC << 9), file);
		return (COMMAND_NON_EXECUTABLE);
	}
	if (S_ISREG(stat_buf.st_mode) == 0 || S_ISDIR(stat_buf.st_mode))
	{
		error_handler(COMMAND_NON_EXECUTABLE | (ERR_ISDIR << 9), file);
		return (COMMAND_NON_EXECUTABLE);
	}
	return (execute_shell_file(file));
}

int				execute_shell_file(char *file)
{
	int		fd;
	char	*line;
	int		status;

	line = NULL;
	status = 0;
	if ((fd = open(file, O_RDONLY)) == -1)
		return (0);
	while (ft_gnl(fd, &line) > 0)
	{
		if ((line && line[0] && line[0] == '#') || !line)
		{
			free(line);
			continue ;
		}
		preparation_noninteractive();
		parser(line);
		line = NULL;
		jobs_clean();
		status = ft_atoi(find_env_value("?"));
	}
	free(line);
	close(fd);
	return (status);
}