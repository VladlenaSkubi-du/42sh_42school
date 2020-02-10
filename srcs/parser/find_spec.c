/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_spec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 13:04:56 by rbednar           #+#    #+#             */
/*   Updated: 2020/02/10 21:29:41 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

/*
** Func to find another subblocks
*/

t_ltree		*ft_find_logic(t_ltree *block, t_ltree *final)
{
	int		i;

	i = block->start;
	final->flags = block->flags;
	final->start = block->start;
	while (i <= block->end)
	{
		if (g_techline.line[i] == PIPE && g_techline.line[i + 1] == PIPE)
		{
			final->end = i - 1;
			final->flags |= LOG_OR;
			return (ft_find_pipe(block, final, &i));
		}
		if (g_techline.line[i] == AND && g_techline.line[i + 1] == AND)
		{
			final->end = i - 1;
			final->flags |= LOG_AND;
			return (ft_find_pipe(block, final, &i));
		}
		if (ft_find_pipe(block, final, &i))
			return (final);
		i++;
	}
	return (NULL);
}

t_ltree		*ft_find_pipe(t_ltree *block, t_ltree *final, int *i)
{
	if (g_techline.line[*i] == PIPE && g_techline.line[*i + 1] != PIPE)
	{
		final->start = block->start;
		final->end = *i;
		(block->flags & PIPED_OUT) && (block->flags |= PIPED_IN);
		(block->flags & PIPED_IN) && (final->flags |= PIPED_IN);
		final->flags |= PIPED_OUT;
		block->flags |= PIPED_OUT;
		return (final);
	}
	if (*i == block->end || final->flags & LOG_AND || final->flags & LOG_OR)
	{
		final->start = block->start;
		final->end = *i;
		*i != block->end && (final->end)--;
		if (block->flags & PIPED_OUT)
		{
			final->flags &= ~PIPED_OUT;
			block->flags &= ~PIPED_OUT;
			final->flags |= PIPED_IN;
			block->flags &= ~PIPED_IN;
		}
		return (final);
	}
	return (NULL);
}


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