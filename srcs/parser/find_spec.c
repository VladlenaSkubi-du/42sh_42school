/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_spec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 13:04:56 by rbednar           #+#    #+#             */
/*   Updated: 2020/02/26 05:25:08 by rbednar          ###   ########.fr       */
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
			final->flags |= LOG_OR;
			return (ft_find_pipe(block, final, &i));
		}
		if (g_techline.line[i] == AND && g_techline.line[i + 1] == AND)
		{
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
	if (*i == block->end || (final->flags & LOG_AND) || (final->flags & LOG_OR))
	{
		final->start = block->start;
		final->end = *i;
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
	size_t	i;

	tmp = block->flags;
	if (!ft_find_logic(block, final))
		return (NULL);
	if (final->end == g_techline.len)
		if ((tmp & LOG_AND) || (tmp & LOG_OR) || 
			(final->flags & PIPED_IN))
		{
			i = final->start - 1;
			while (++i < g_techline.len)
			{
				if (g_techline.line[i] != SPACE) // обработка ошибок!!! 
					break;		// syntax error near unexpected token `;'
			}
			if (i == g_techline.len && ((tmp & LOG_AND) || (tmp & LOG_OR)))
				g_prompt.prompt_func = cmdandor_prompt;
			else if (i == g_techline.len && (final->flags & PIPED_IN))
				g_prompt.prompt_func = pipe_prompt;
		}
	return (final);			
}

/*
** Function clear list of t_ltree type
*/

void	ft_lst_ltree_clear(t_list **begin_list)
{
	t_list 	*tmp;
	t_ltree	*buf;

	if (!(begin_list) || !(*begin_list))
		return ;
	while (*begin_list)
	{
		tmp = (*begin_list)->next;
		if ((*begin_list)->content)
		{
			buf = (t_ltree *)(*begin_list)->content;
			free(buf->l_cmd);
			free(buf->l_techline.line);
			ft_arrdel(buf->envir);
			ft_arrdel(buf->ar_v);
			ft_lstclear(&buf->fd);
			free(buf->err);
			free((*begin_list)->content);
		}
		free((*begin_list));
		*begin_list = tmp;
	}
	*begin_list = NULL;
}
