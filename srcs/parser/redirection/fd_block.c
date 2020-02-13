/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_block.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:16:37 by rbednar           #+#    #+#             */
/*   Updated: 2020/02/13 19:24:47 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

/*
** Function to add redirection rule to block before execve
** uses address of block, fd in and out and type of redirection input/output
*/

int		add_redir_fd(t_ltree *final, t_fd_redir *redir)
{
	t_list		*new;
	t_fd_redir	*fd_work;

	new = (t_list *)ft_xmalloc(sizeof(t_list));
	new->content = (void *)ft_xmalloc(sizeof(t_fd_redir));
	new->content_size = sizeof(t_fd_redir);
	fd_work = (t_fd_redir *)new->content;
	fd_work->fd_out = redir->fd_out;
	fd_work->fd_in = redir->fd_in;
	fd_work->type = redir->type;
	ft_add_list_to_end(&(final->fd), new);
	return (0);
}

/*
** Must be used to check if is IO_NUMBER before redirection operator or not
** std is standart input or output
*/

int		ft_check_n_redir_op(size_t i, t_ltree *final, int std)
{
	char	*find;

	find = ft_word_to_redir(&i, final, REW);
	if (find)
	{
		while (*find)
		{
			if (*find == TEXT)
			{
				free(find);
				return (std);
			}
			(*find)++;
		}
		free(find);
		return (ft_atoi(find));
	}
	return (std);
}

/*
** Must be used to check if is IO_NUMBER after redirection operator or not
** std is standart input or output
*/

int		ft_check_redir_op_n(size_t i, t_ltree *final, int std)
{
	char	*find;

	find = ft_word_to_redir(&i, final, FF);
	if (find)
	{
		while (*find)
		{
			if (*find == TEXT)
			{
				free(find);
				return (std);
			}
			(*find)++;
		}
		free(find);
		return (ft_atoi(find));
	}
	return (std);
}