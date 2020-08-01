/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_types_out_do.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 13:24:26 by rbednar           #+#    #+#             */
/*   Updated: 2020/08/01 15:23:10 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

/*
** Function to do redirectionsin block
*/

void	ft_find_redirection_do(t_ltree *final)
{
	t_list		*fd_list;
	t_fd_redir	*redir;

	fd_list = final->fd;
	while (fd_list)
	{
		redir = ((t_fd_redir *)fd_list->content);
		if (redir->type == GREAT)
			if (ft_redir_great_do(final, redir))
				break ;
		if (redir->type == DGREAT)
			if (ft_redir_dgreat_do(final, redir))
				break ;
		if (redir->type == GREATAND)
			if (ft_redir_greatand_do(final, redir))
				break ;
		if (redir->type == LESS)
			if (ft_redir_less_do(final, redir))
				break ;
		if (redir->type == LESSAND)
			if (ft_redir_lessand_do(final, redir))
				break ;
		fd_list = fd_list->next;
	}
}

/*
** Function to do "[n]>word"
*/

int		ft_redir_great_do(t_ltree *final, t_fd_redir *fd)
{
	if ((fd->fd_old = open(fd->name, O_CREAT | O_RDWR | O_TRUNC |
	O_CLOEXEC | O_NDELAY | O_NOCTTY, 00666)) == -1)
		return (ft_access_check(&fd->name, final, W_OK));
	return (0);
}

/*
** Function to do ">>word" (write to end)
*/

int		ft_redir_dgreat_do(t_ltree *final, t_fd_redir *fd)
{
	if ((fd->fd_old = open(fd->name, O_CREAT | O_RDWR | O_APPEND |
	O_CLOEXEC | O_NDELAY | O_NOCTTY, 00666)) == -1)
		return (ft_access_check(&fd->name, final, W_OK));
	return (0);
}

/*
** Function to do "[n]>&[m]"
** fcntl used to check access to write in fd
*/

int		ft_redir_greatand_do(t_ltree *final, t_fd_redir *fd)
{
	return (ft_num_or_word_out(&fd->name, fd, final));
}
