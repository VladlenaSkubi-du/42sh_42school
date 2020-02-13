/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_types_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 14:04:36 by rbednar           #+#    #+#             */
/*   Updated: 2020/02/13 20:26:31 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

/*
** Function to detect ">"
*/

int		ft_redir_gthen(t_ltree *final, size_t *i)
{
	t_fd_redir	fd_open;
	char		*f_name;

	f_name = NULL;
	fd_open.type = OUT_R;
	if (g_techline.line[*i] == GTHAN && (g_techline.line[*i + 1] != GTHAN &&
		(g_techline.line[*i + 1] != AND || g_techline.line[*i + 1] == PIPE)))
	{
		fd_open.fd_out = ft_check_n_redir_op(*i, final, STDOUT_FILENO);
		ft_null_redir(*i, 1);
		(*i)++;
		if ((f_name = ft_word_to_redir(i, final, FF)) != NULL)
		{
			if ((fd_open.fd_in = open(f_name, O_CREAT | O_WRONLY | O_TRUNC |
			O_CLOEXEC | O_SYNC | O_NOCTTY, S_IRWXU)) == -1)
				return (ft_error_redir(final, *i, ERR_NO_ACC, &f_name));
			else
				add_redir_fd(final, &fd_open);
		}
		else
			return (ft_error_redir(final, *i, ERR_REDIR, NULL));
	}
	(f_name != NULL) ? free(f_name) : 0;
	return (0);
}

/*
** Function to detect ">>"
*/

int		ft_redir_ggthen(t_ltree *final, size_t *i)
{
	t_fd_redir	fd_open;
	char		*f_name;

	f_name = NULL;
	fd_open.type = OUT_R;
	if (g_techline.line[*i] == GTHAN && g_techline.line[*i + 1] == GTHAN)
	{
		fd_open.fd_out = ft_check_n_redir_op(*i, final, STDOUT_FILENO);
		ft_null_redir(*i, 2);
		(*i) += 2;
		if ((f_name = ft_word_to_redir(i, final, FF)) != NULL)
		{
			if ((fd_open.fd_in = open(f_name, O_CREAT | O_WRONLY | O_APPEND |
			O_CLOEXEC | O_SYNC | O_NOCTTY, S_IRWXU)) == -1)
				return (ft_error_redir(final, *i, ERR_NO_ACC, &f_name));
			else
				add_redir_fd(final, &fd_open);
		}
		else
			return (ft_error_redir(final, *i, ERR_REDIR, NULL));
	}
	(f_name != NULL) ? free(f_name) : 0;
	return (0);
}

/*
** Function to detect ">&"
*/

int		ft_redir_gathen(t_ltree *final, size_t *i)
{
	t_fd_redir	fd_open;
	char		*f_name;

	f_name = NULL;
	fd_open.type = OUT_R;
	if (g_techline.line[*i] == GTHAN && (g_techline.line[*i + 1] == AND))
	{
		fd_open.fd_out = ft_check_n_redir_op(*i, final, STDOUT_FILENO);
		ft_null_redir(*i, 2);
		(*i) += 2;
		if ((f_name = ft_word_to_redir(i, final, FF)) != NULL)
		{
			if (((fd_open.fd_in = fcntl(ft_atoi(f_name), F_GETFL)) & O_ACCMODE)
				!= O_RDWR && (fd_open.fd_in & O_ACCMODE) != O_WRONLY)
				return (ft_error_redir(final, *i, ERR_BAD_FD, &f_name));
			else
				fd_open.fd_in = ft_atoi(f_name) >= 0 ?
				add_redir_fd(final, &fd_open) : 0;
		}
		else
			return (ft_error_redir(final, *i, ERR_REDIR, NULL));
	}
	(f_name != NULL) ? free(f_name) : 0;
	return (0);
}
