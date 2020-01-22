/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_spec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 13:04:56 by rbednar           #+#    #+#             */
/*   Updated: 2020/01/22 13:04:56 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Func to find another subblocks
*/

t_ltree		*ft_find_pipe(t_ltree *block, t_ltree *final)
{
	int		i;
	
	i = block->start;
	while (i <= block->end)
	{
		if (g_techline.line[i] == PIPE)
		{
			final->start = block->start;
			final->end = i;
			(block->flags & PIPED_OUT) && (block->flags |= PIPED_IN);
			(block->flags & PIPED_IN) && (final->flags |= PIPED_IN);
			final->flags |= PIPED_OUT;
			block->flags |= PIPED_OUT;
			return (final);
		}
		if (i == block->end)
		{
			final->start = block->start;
			final->end = i;
			if (block->flags & PIPED_OUT)
			{
				final->flags = PIPED_IN;
				block->flags = PIPED_IN;
			}
			return (final);
		}
		i++;
	}
	return (NULL); //need to add subfunctions to detect symbols in block .using g_techline and rules for all types
}
