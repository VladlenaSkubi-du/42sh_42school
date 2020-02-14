/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_types_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 14:04:36 by rbednar           #+#    #+#             */
/*   Updated: 2020/02/14 21:01:28 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

/*
** Function to detect "[n]>word"
*/

int		ft_redir_great(t_ltree *final, size_t *i)
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
			O_CLOEXEC | O_SYNC | O_NOCTTY, S_IRUSR | S_IWUSR)) == -1)
				return (ft_access_check(&f_name, final, i, S_IWUSR));
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
** Function to detect ">>word" (write to end)
*/

int		ft_redir_dgreat(t_ltree *final, size_t *i)
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
				O_CLOEXEC | O_SYNC | O_NOCTTY, S_IRUSR | S_IWUSR)) == -1)
				return (ft_access_check(&f_name, final, i, S_IWUSR));
			else
				add_redir_fd(final, &fd_open);
		}
		else
			return (ft_error_redir(final, *i, ERR_REDIR, NULL));
	}
	free(f_name);
	return (0);
}

/*
** Function to detect "[n]>&[m]"
** fcntl used to check access to write in fd
*/

int		ft_redir_greatand(t_ltree *final, size_t *i)
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
			return (ft_num_or_word_out(&f_name, &fd_open, i, final));
		else
			return (ft_error_redir(final, *i, ERR_REDIR, NULL));
	}
	free(f_name);
	return (0);
}

/*
** Function needs to check access rights
*/

int		ft_access_check(char **f_name, t_ltree *final, size_t *i, int type)
{
	t_stat	*statbuf;
	char 	*path;
	int		st;

	statbuf = (t_stat *)ft_xmalloc(sizeof(t_stat));
	path = (char*)ft_xmalloc(MAXDIR);
	getcwd(path, MAXDIR);
	if (path[0] == 0)
		free(path);
	ft_strcat(path, "/");
	ft_strcat(path, *f_name);
	if ((st = stat(path, statbuf)) != -1)
		if ((statbuf->st_mode & type) == 0)
		{
			free(path);
			free(statbuf);
			return (ft_error_redir(final, *i, ERR_NO_ACC, f_name));
		}
	free(path);
	free(statbuf);
	return (ft_error_redir(final, *i, ERR_NO_FILE, f_name));
}
