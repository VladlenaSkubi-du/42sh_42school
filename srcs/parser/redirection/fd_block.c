/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_block.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:16:37 by rbednar           #+#    #+#             */
/*   Updated: 2020/02/14 20:29:05 by rbednar          ###   ########.fr       */
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
	int		ret;

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
		ret = ft_atoi(find);
		free(find);
		return (ret);
	}
	return (std);
}

/*
** Must be used to check if is IO_NUMBER after redirection operator or not
** std is standart input or output
*/

int		ft_check_redir_op_n(char *find, int std)
{
	char	*buf;

	buf = find;
	if (buf)
	{
		while (*buf)
		{
			if (*buf == TEXT || !(ft_isdigit(*find)))
				return (std);
			buf++;
		}
		return (ft_atoi(find));
	}
	return (std);
}

/*
** Must be used to check if is IO_NUMBER after redirection operator or not
** add fd or filename's fd
*/

int		ft_num_or_word_out(char **f_name, t_fd_redir *fd_open,
						size_t *i, t_ltree *final)
{
	int		fd_ret;

	if ((fd_ret = ft_check_redir_op_n(*f_name, -1)) == -1)
	{
		if (!(ft_strcmp(*f_name, "-")))
			(fd_open->fd_in = CLOSE) >= 0 ? add_redir_fd(final, fd_open) : 0;
		else if ((fd_open->fd_in = open(*f_name, O_CREAT | O_WRONLY | O_TRUNC |
			O_CLOEXEC | O_SYNC | O_NOCTTY, S_IRUSR | S_IWUSR)) == -1)
			return (ft_access_check(f_name, final, i, S_IWUSR));
		else
			add_redir_fd(final, fd_open);
	}
	else
	{
		if (((fd_open->fd_in = fcntl(fd_ret, F_GETFL)) & O_ACCMODE)
			!= O_WRONLY && (fd_open->fd_in & O_ACCMODE) != O_RDWR)
			return (ft_error_redir(final, *i, ERR_BAD_FD, f_name));
		else
			(fd_open->fd_in = fd_ret) >= 0 ?
			add_redir_fd(final, fd_open) : 0;
	}
	return (0);
}

int		ft_num_or_word_in(char **f_name, t_fd_redir *fd_open,
							size_t *i, t_ltree *final)
{
	int		fd_ret;

	if ((fd_ret = ft_check_redir_op_n(*f_name, -1)) == -1)
	{
		if (!(ft_strcmp(*f_name, "-")))
			(fd_open->fd_out = CLOSE) >= 0 ? add_redir_fd(final, fd_open) : 0;
		else if ((fd_open->fd_in = open(*f_name, O_RDONLY |
			O_CLOEXEC | O_SYNC | O_NOCTTY)) == -1)
			return (ft_access_check(f_name, final, i, S_IRUSR));
		else
			add_redir_fd(final, fd_open);
	}
	else
	{
		if (((fd_open->fd_out = fcntl(fd_ret, F_GETFL)) & O_ACCMODE)
			!= O_WRONLY && (fd_open->fd_out & O_ACCMODE) != O_RDWR)
			return (ft_error_redir(final, *i, ERR_BAD_FD, f_name));
		else
			(fd_open->fd_out = fd_ret) >= 0 ?
			add_redir_fd(final, fd_open) : 0;
	}
	return (0);
}
