/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_types_in_do.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 14:45:56 by rbednar           #+#    #+#             */
/*   Updated: 2020/08/18 21:47:54 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

/*
** Function to detect "[n]<word"
*/

int		ft_redir_less_do(t_ltree *final, t_fd_redir *fd)
{
	if ((fd->fd_old = open(fd->name, O_RDONLY | O_CLOEXEC |
	O_NDELAY | O_NOCTTY, S_IRUSR)) == -1)
		return (ft_access_check(&fd->name, final, R_OK));
	return (0);
}

/*
** Function to detect "[n]<&[m]" (input from fd or file if)
*/

int		ft_redir_lessand_do(t_ltree *final, t_fd_redir *fd)
{
	return (ft_num_or_word_in(&fd->name, fd, final));
}

int		ft_redir_valid(t_ltree *final, int i)
{
	char	*line;

	line = final->l_tline.line;
	if ((((line[i] == GTHAN && line[i + 1] == GTHAN) ||
		(line[i] == LTHAN && line[i + 1] == LTHAN) ||
		(line[i] == GTHAN && line[i + 1] == AND) ||
		(line[i] == LTHAN && line[i + 1] == AND)) &&
		(line[i + 2] != GTHAN && line[i + 2] != LTHAN &&
		line[i + 2] != AND)) ||
		((line[i] == GTHAN || line[i] == LTHAN) &&
		(line[i + 1] == SPACE || line[i + 1] == WORD_P ||
		line[i + 1] == TEXT)))
		return (1);
	return (0);
}
