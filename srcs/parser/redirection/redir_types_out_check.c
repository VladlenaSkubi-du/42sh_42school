/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_types_out_check.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:55:29 by rbednar           #+#    #+#             */
/*   Updated: 2020/08/25 22:01:57 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

int		ft_redir_check(t_ltree *final)
{
	int		i;
	int		ret;

	i = final->start;
	ret = 0;
	while (i <= final->end)
	{
		if (final->l_tline.line[i] == GTHAN || final->l_tline.line[i] == LTHAN)
		{
			if (ft_redir_valid(final, i))
			{
				if ((ret = ft_find_redirection_check(final, &i)) != 0)
				{
					final->err_i = i;
					return (ret);
				}
			}
			else
				return (final->flags |= ERR_OUT | ERR_REDIR << 16);
		}
		i++;
	}
	return (0);
}

/*
** Function to detect "[n]>word"
*/

int		ft_redir_great_check(t_ltree *final, int *i)
{
	t_fd_redir	fd;

	fd.name = NULL;
	if (final->l_tline.line[*i] == GTHAN && (final->l_tline.line[*i + 1] !=
		GTHAN && (final->l_tline.line[*i + 1] != AND ||
		final->l_tline.line[*i + 1] == PIPE)))
	{
		fd.type = GREAT;
		fd.fd_new = ft_check_n_redir_op(*i, final, STDOUT_FILENO);
		!ft_null_redir(final, *i, 1) ? (*i)++ : 0;
		if ((fd.name = ft_word_to_redir(i, final, FF)) != NULL)
			add_redir_fd(final, &fd);
		else
			return (final->flags |= ERR_OUT | ERR_REDIR << 16);
	}
	free(fd.name);
	return (0);
}

/*
** Function to detect ">>word" (write to end)
*/

int		ft_redir_dgreat_check(t_ltree *final, int *i)
{
	t_fd_redir	fd;

	fd.name = NULL;
	if (final->l_tline.line[*i] == GTHAN &&
		final->l_tline.line[*i + 1] == GTHAN)
	{
		fd.type = DGREAT;
		fd.fd_new = ft_check_n_redir_op(*i, final, STDOUT_FILENO);
		ft_null_redir(final, *i, 2);
		(*i) += 2;
		if ((fd.name = ft_word_to_redir(i, final, FF)) != NULL)
			add_redir_fd(final, &fd);
		else
			return (final->flags |= ERR_OUT | ERR_REDIR << 16);
	}
	free(fd.name);
	return (0);
}

/*
** Function to detect "[n]>&[m]"
** fcntl used to check access to write in fd
*/

int		ft_redir_greatand_check(t_ltree *final, int *i)
{
	t_fd_redir	fd;

	fd.name = NULL;
	if (final->l_tline.line[*i] == GTHAN &&
		(final->l_tline.line[*i + 1] == AND))
	{
		fd.type = GREATAND;
		fd.fd_new = ft_check_n_redir_op(*i, final, STDOUT_FILENO);
		ft_null_redir(final, *i, 2);
		(*i) += 2;
		if ((fd.name = ft_word_to_redir(i, final, FF)) != NULL)
			add_redir_fd(final, &fd);
		else
			return (final->flags |= ERR_OUT | ERR_REDIR << 16);
	}
	free(fd.name);
	return (0);
}

/*
** Function needs to check access rights
*/

int		ft_access_check(char **f_name, t_ltree *final, int type)
{
	char	*path;
	int		st;

	if (*f_name[0] != '/')
	{
		path = getcwd(NULL, MAXDIR);
		ft_strcat(path, "/");
		ft_strcat(path, *f_name);
	}
	else
		path = ft_strdup(*f_name);
	final->err = ft_strdup(*f_name);
	if ((st = access(path, F_OK)) == -1)
	{
		free(path);
		return (final->flags |= ERR_IN | ERR_R | ERR_NO_FILE << 16);
	}
	if ((st = access(path, type)) == -1)
	{
		free(path);
		return (final->flags |= ERR_IN | ERR_R | ERR_NO_ACC << 16);
	}
	return (0);
}
