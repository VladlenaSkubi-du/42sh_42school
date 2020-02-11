/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 13:46:57 by rbednar           #+#    #+#             */
/*   Updated: 2020/02/11 13:50:10 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

int			ft_find_redirection(t_ltree *final)
{
	size_t	i;
	int		fd_open;
	
	i = final->start;	
	while (i < final->end)
	{
		if (g_techline.line[i] == GTHAN && (g_techline.line[i + 1] != GTHAN &&
			(g_techline.line[i + 1] != AND || g_techline.line[i + 1] == PIPE))) //Braces corrected
		{
			if ((fd_open = ft_atoi(&g_cmd[i + 1])) >= 0)
				final->fd[1] = fd_open;
			else if ((fd_open = open(((const char *)ft_word_to_redir()), \
					O_CREAT | O_WRONLY | O_TRUNC | O_CLOEXEC | O_SYNC | \
					O_NOCTTY, S_IRWXU)) != -1)
				final->fd[1] = fd_open;
		}
		i++;
	}
	return (0);
}

char		*ft_word_to_redir(void) //Correct
{
	char	*file;

	file = NULL;

	return (file);
}