/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:13:51 by hshawand          #+#    #+#             */
/*   Updated: 2020/08/23 17:12:19 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"
#include "builtin42.h"
#include "builtins_list.h"

/*
** So, let's talk about pipes:
** 1) If only PIPED_OUT -- create pipe
** 2) If only PIPED_IN -- delete pipe
*/

int		exec_clean(char *path, int exit_status, char *err_msg)
{
	int			error;

	error = (exit_status == -1) ? get_command_error() : exit_status;
	if (error != 0)
	{
		error_handler(error, get_command_error_name());
	}
	exit_status_variables(error & 0x7F);
	free(path);
	if (err_msg)
		ft_putendl_fd(err_msg, STDERR_FILENO);
	return (exit_status);
}

/*
** Check if programm to start is buildin and if it is - start builtin
*/

int		ft_builtins_check(t_process *p, int flag)
{
	int		i;
	int		ret;

	i = 0;
	while (g_builtins[i])
	{
		if (!ft_strcmp(p->argv[0], g_builtins[i]))
		{
			if (flag)
			{
				ret = g_builtins_func[i](p);
				p->completed = 1;
				return(ret & 0x7F);
			}
			return (i);
		}
		i++;
	}
	return (-1);
}

int		fd_list_process(t_process *pos, int flag)
{
	t_list		*fd_list;
	t_fd_redir	*redir;

	fd_list = pos->fd;
	while (fd_list)
	{
		redir = (t_fd_redir *)fd_list->content;
		if (flag == CLOSE && redir->fd_old != 1 && redir->fd_old != 2
			&& redir->fd_old != 0)
			close(redir->fd_old);
		else if (redir->fd_old != CLOSE)
			dup2(redir->fd_old, redir->fd_new);
		else
			close(redir->fd_new);
		fd_list = fd_list->next;
	}
	return (0);
}

int		path_init_errors(char *exec_av, char *name)
{
	int			flag;
	struct stat	stat_buf;

	if (access(exec_av, F_OK) == -1)
	{
		save_command_error(COMMAND_NOT_FOUND | (ERR_COMMAND << 9), name);
		exit_status_variables((COMMAND_NOT_FOUND | (ERR_COMMAND << 9)) & 0x7F);
		// error_handler(COMMAND_NOT_FOUND |
		// 	(ERR_COMMAND << 9), name);
		return (-1);
	}
	flag = 0;
	if (access(exec_av, X_OK) == -1 || stat(exec_av, &stat_buf) != 0
			|| (stat_buf.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)) == 0 ||
			S_ISREG(stat_buf.st_mode) == 0)
		flag |= COMMAND_NON_EXECUTABLE;
	if (flag & COMMAND_NON_EXECUTABLE)
	{
		if (stat(exec_av, &stat_buf) == 0 && S_ISDIR(stat_buf.st_mode))
		{
			save_command_error(COMMAND_NON_EXECUTABLE | (ERR_ISDIR << 9), name);
			exit_status_variables((COMMAND_NON_EXECUTABLE | (ERR_ISDIR << 9)) & 0x7F);
			// error_handler(COMMAND_NON_EXECUTABLE | (ERR_ISDIR << 9), name);
		}
		else
		{
			save_command_error(COMMAND_NON_EXECUTABLE | (ERR_NO_ACC << 9), name);
			exit_status_variables((COMMAND_NON_EXECUTABLE | (ERR_NO_ACC << 9)) & 0x7F);
			// error_handler(COMMAND_NON_EXECUTABLE | (ERR_NO_ACC << 9), name);
		}
		return (-1);
	}
	return (0);
}
