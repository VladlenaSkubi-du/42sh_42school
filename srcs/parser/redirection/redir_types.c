/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 14:04:36 by rbednar           #+#    #+#             */
/*   Updated: 2020/02/12 16:57:10 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

/*
** Function to detect ">"
*/

int		ft_redir_gthen(t_ltree *final, size_t *i)
{
	int		fd_open;
	char	*f_name;

	f_name = NULL;
	if (g_techline.line[*i] == GTHAN && (g_techline.line[*i + 1] != GTHAN &&
		(g_techline.line[*i + 1] != AND || g_techline.line[*i + 1] == PIPE)))
	{
		ft_null_redir(*i, 1);
		(*i)++;
		if (ft_isdigit(g_techline.line[*i]))
			final->fd[1] = ft_atoi(&g_cmd[*i + 1]);
		else if ((f_name = ft_word_to_redir(i, final)) != NULL &&
			(fd_open = open(f_name, O_CREAT | O_WRONLY | O_TRUNC | O_CLOEXEC |
			O_SYNC | O_NOCTTY, S_IRWXU)) != -1)
			final->fd[1] = fd_open;
		else
			return (ft_error_redir(final, *i));
	}
	(f_name != NULL) ? free(f_name) : 0;
	return (0);
}
