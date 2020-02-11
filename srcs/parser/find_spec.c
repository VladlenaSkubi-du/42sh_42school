/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_spec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 13:04:56 by rbednar           #+#    #+#             */
/*   Updated: 2020/02/11 16:04:32 by rbednar          ###   ########.fr       */
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

t_ltree		*ft_check_andor_pipes(t_ltree *block, t_ltree *final, t_list **list)
{
	int		tmp;
	t_ltree	*sub;
	size_t	i;

	tmp = final->flags;
	sub = ft_find_logic(block, final);
	if (!sub)
		return (sub);
	if (sub->end == g_techline.len)
		if (tmp & LOG_AND || tmp & LOG_OR || 
			sub->flags & PIPED_IN)
		{
			i = sub->start - 1;
			while (++i <= g_techline.len)
			{
				if (g_techline.line[i] == 0)
					break;
			}
			if (i == g_techline.len && (tmp & LOG_AND || tmp & LOG_OR))
				g_prompt.prompt_func = cmdandor_prompt;
			else if (i == g_techline.len && sub->flags & PIPED_IN)
				g_prompt.prompt_func = pipe_prompt;
		}
	return (sub);			
}