/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice_to_blocks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 15:01:01 by rbednar           #+#    #+#             */
/*   Updated: 2020/02/12 16:07:59 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

/*
** Function add commands whith args and fd to list
*/

int		ft_block_add_to_list(t_ltree *block, t_list **list)
{
	t_ltree	*sub;
	t_ltree	final;
	int		k;

	while ((sub = ft_check_andor_pipes(block, &final, list)))
	{
		k = -1;
		while (++k <= 2)
			final.fd[k] = k;
		if ((k = ft_find_redirection(&final)) == OUT)
		{
			ft_lstclear(list);
			return (OUT);
		}
		ft_add_list_to_end(list, ft_lstnew(&final, sizeof(t_ltree)));
		block->flags &= ~GR_START;
		block->start = final.end + 1;
		final.end = block->end;
		if (final.flags & LOG_AND || final.flags & LOG_OR)
			block->start += 2;
	}
	return (0);
}

/*
** Function forwards list commands until GR_START
*/

int		ft_block_foward(t_ltree **sub, t_list **start)
{
	while (*start)
	{
		if ((*start = (*start)->next))
			*sub = (t_ltree *)((*start)->content);
		else
			break ;
		if ((*sub)->flags & GR_START)
			break ;
	}
	return (0);
}

/*
** Function start list commands
*/

int		ft_block_start(t_list **list)
{
	t_ltree	*sub;
	t_list	*start;
	int		out_flag;

	start = *list;
	while (start)
	{
		sub = (t_ltree *)(start->content);
		out_flag = exec_init(sub);
		if (out_flag != 0 && (sub->flags & LOG_AND))
			ft_block_foward(&sub, &start);
		else if (out_flag == 0 && (sub->flags & LOG_OR))
			ft_block_foward(&sub, &start);
		else
			start = start->next;
	}
	ft_lstclear(list);
	return (0);
}

/*
** Fucntion slice command string to blocks and send add it to start
** list with BG flag
*/

int		ft_slice_bg(size_t *i, t_ltree *block, t_list **start_list)
{
	if (g_techline.line[*i] == AND && g_techline.line[*i + 1] != AND && \
		g_techline.line[*i - 1] != AND && \
		g_techline.line[*i + 1] != GTHAN && \
		g_techline.line[*i + 1] != LTHAN && \
		g_techline.line[*i - 1] != GTHAN && g_techline.line[*i - 1] != LTHAN)
	{
		block->end = *i;
		block->flags |= IS_BG;
		if (ft_block_add_to_list(block, start_list) == OUT)
			return (OUT);
		block->start = *i + 1;
	}
	return (0);
}

/*
** Fucntion slice command string to blocks and send add it to start list
*/

int		ft_slice_fg(void)
{
	t_ltree			block;
	size_t			i;
	t_list			*start_list;

	i = -1;
	while (++i <= 2)
		block.fd[i] = i;
	i = -1;
	block.start = 0;
	start_list = NULL;
	while (++i <= g_techline.len)
	{
		block.flags = GR_START;
		if (ft_slice_bg(&i, &block, &start_list) == OUT)
			return (OUT);
		if (g_techline.line[i] == SCOLON || g_cmd[i] == '\0')
		{
			block.end = i;
			if (ft_block_add_to_list(&block, &start_list) == OUT)
				return (OUT);
			block.start = i + 1;
		}
	}
	(g_prompt.prompt_func == main_prompt) ? ft_block_start(&start_list) : 0;
	return (0);
}
