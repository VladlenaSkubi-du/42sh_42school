/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_spec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 13:04:56 by rbednar           #+#    #+#             */
/*   Updated: 2020/01/22 17:16:36 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Func to find another subblocks
*/

t_ltree		*ft_find_logic(t_ltree *block, t_ltree *final)
{
	int 	i;
	t_ltree buf;

	i = block->start;
	final->flags = 0;
	while (i < block->end)
	{
		if (g_techline.line[i] == PIPE && g_techline.line[i + 1] == PIPE)
		{
			buf.start = block->start;
			block->start = i + 2;
			buf.end = i - 1;
			block->flags = LOG_OR;
			buf.flags = block->flags;
			return (ft_find_logic(&buf, final));
		}
		if (ft_find_pipe(block, final, &i))
			return (final);
		i++;
	}
	return (NULL);
}

t_ltree		*ft_find_pipe(t_ltree *block, t_ltree *final, int *i)
{
	if (g_techline.line[*i] == PIPE)
	{
		final->start = block->start;
		final->end = *i;
		(block->flags & PIPED_OUT) && (block->flags |= PIPED_IN);
		(block->flags & PIPED_IN) && (final->flags |= PIPED_IN);
		final->flags |= PIPED_OUT;
		block->flags |= PIPED_OUT;
		return (final);
	}
	if (*i == block->end)
	{
		final->start = block->start;
		final->end = *i;
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
