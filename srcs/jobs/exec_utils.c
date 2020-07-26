/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshawand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:13:51 by hshawand          #+#    #+#             */
/*   Updated: 2020/07/26 16:37:05 by hshawand         ###   ########.fr       */
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

int	exec_clean(char *path, int exit_status, char *err_msg)
{
	if (path)
		exit_status_variables(exit_status);
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
	t_ltree	xXx_PLACEHOLDER_xXx; // Hi, have you decided to fix norme error? Well, screw you! First of all, fix builtins and this function!

	i = 1;
	while (g_builtins[i])
	{
		if (!ft_strcmp(p->argv[0], g_builtins[i]))
		{
			if (flag)
			{
				xXx_PLACEHOLDER_xXx.ar_c = p->argc;
				vec_dup(&xXx_PLACEHOLDER_xXx.ar_v, p->argv);
				vec_dup(&xXx_PLACEHOLDER_xXx.envir, p->envp);
				exit_status_variables(g_builtins_func[i](&xXx_PLACEHOLDER_xXx));
				ft_arrdel(xXx_PLACEHOLDER_xXx.ar_v);
				ft_arrdel(xXx_PLACEHOLDER_xXx.envir);
				p->completed = 1;
			}
			return (i);
		}
		i++;
	}
	return (-1);
}

int		fd_list_process(t_ltree *pos, int mode)
{
	t_list		*fd_list;
	t_fd_redir	*redir;

	if (!mode)
	{
		std_save(0);
		fd_list = pos->fd;
		while (fd_list)
		{
			redir = (t_fd_redir *)fd_list->content;
			if (redir->fd_old != CLOSE)
				dup2(redir->fd_old, redir->fd_new);
			else
			{
				dup2(redir->fd_new, redir->fd_new);
				close(redir->fd_new);
			}
			fd_list = fd_list->next;
		}
	}
	else
		std_save(1);
	return (0);
}
