/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_types_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:20:07 by rbednar           #+#    #+#             */
/*   Updated: 2020/02/14 21:04:31 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

/*
** Function to detect "[n]< word"
*/

int		ft_redir_less(t_ltree *final, size_t *i)
{
	t_fd_redir	fd_open;
	char		*f_name;

	f_name = NULL;
	fd_open.type = IN_R;
	if (g_techline.line[*i] == LTHAN && (g_techline.line[*i + 1] != LTHAN &&
		(g_techline.line[*i + 1] != AND || g_techline.line[*i + 1] == PIPE)))
	{
		fd_open.fd_in = ft_check_n_redir_op(*i, final, STDIN_FILENO);
		ft_null_redir(*i, 1);
		(*i)++;
		if ((f_name = ft_word_to_redir(i, final, FF)) != NULL)
		{
			if ((fd_open.fd_out = open(f_name, O_RDONLY |
			O_CLOEXEC | O_SYNC | O_NOCTTY)) == -1)
				return (ft_access_check(&f_name, final, i, S_IRUSR));
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
** Function to detect "[n]<<stop_word" here-document
*/

int		ft_redir_dless(t_ltree *final, size_t *i)
{
	t_fd_redir	fd_open;
	char		*f_name;

	f_name = NULL;
	fd_open.type = IN_R;
	if (g_techline.line[*i] == LTHAN && g_techline.line[*i + 1] == LTHAN)
	{
		fd_open.fd_in = ft_check_n_redir_op(*i, final, STDIN_FILENO);
		ft_null_redir(*i, 2);
		(*i) += 2;
		if ((f_name = ft_word_to_redir(i, final, FF)) != NULL)
		{
			//here document
		}
		else
			return (ft_error_redir(final, *i, ERR_REDIR, NULL));
	}
	free(f_name);
	return (0);
}

/*
** Function to detect "[n]<&[m]" (input from fd or file if)
*/

int		ft_redir_lessand(t_ltree *final, size_t *i)
{
	t_fd_redir	fd_open;
	char		*f_name;

	f_name = NULL;
	fd_open.type = IN_R;
	if (g_techline.line[*i] == LTHAN && (g_techline.line[*i + 1] == AND))
	{
		fd_open.fd_in = ft_check_n_redir_op(*i, final, STDIN_FILENO);
		ft_null_redir(*i, 2);
		(*i) += 2;
		if ((f_name = ft_word_to_redir(i, final, FF)) != NULL)
			return (ft_num_or_word_in(&f_name, &fd_open, i, final));
		else
			return (ft_error_redir(final, *i, ERR_REDIR, NULL));
	}
	free(f_name);
	return (0);
}
