/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_spec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 13:04:56 by rbednar           #+#    #+#             */
/*   Updated: 2020/01/31 12:02:43 by rbednar          ###   ########.fr       */
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
	final->flags = 0;
	final->start = block->start;
	while (i <= block->end)
	{
		if (g_techline.line[i] == PIPE && g_techline.line[i + 1] == PIPE)
		{
			final->end = i - 1;
			final->flags = LOG_OR;
			return (ft_find_pipe(block, final, &i));
		}
		if (g_techline.line[i] == AND && g_techline.line[i + 1] == AND)
		{
			final->end = i - 1;
			final->flags = LOG_AND;
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
			block->flags |= PIPED_IN;
		}
		return (final);
	}
	return (NULL);
}
