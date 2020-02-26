/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice_to_blocks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 15:01:01 by rbednar           #+#    #+#             */
/*   Updated: 2020/02/26 16:39:08 by rbednar          ###   ########.fr       */
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
	t_ltree	*final;

	final = (t_ltree *)ft_xmalloc(sizeof(t_ltree));
	while ((sub = ft_check_andor_pipes(block, final, list)))
	{
		if (sub->flags & ERR_OUT)
		{
			ft_lst_ltree_clear(list);
			return (OUT);
		}
		block->flags &= ~GR_START;
		block->start = final->end + 1;
		before_exec(final, block);
		ft_add_list_to_end(list, ft_lstnew(final, sizeof(t_ltree)));
		if (final->flags & LOG_AND || final->flags & LOG_OR)
			block->start += 1;
		ltree_init(final);
	}
	free(final);
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
		if (!(sub->flags & ERR_IN))
		{
			out_flag = exec_init(sub); //внутри exec выбор: builtin или нет
			if ((out_flag != 0 && (sub->flags & LOG_AND)) ||
				(out_flag == 0 && (sub->flags & LOG_OR)))
				ft_block_foward(&sub, &start);
		}
		else if (sub->flags & ERR_R)
			ft_error_redir(sub);
		if (start)
			start = start->next;
	}
	ft_lst_ltree_clear(list);
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

	i = -1;
	ltree_init(&block);
	if (g_prompt.prompt_func != heredoc_prompt)
	{
		g_heredoc.list = NULL;
		g_start_list = NULL;
		while (++i <= g_techline.len)
		{
			block.flags = GR_START;
			if (ft_slice_bg(&i, &block, &g_start_list) == OUT)
				return (OUT);
			if (g_techline.line[i] == SCOLON || g_cmd[i] == '\0')
			{
				block.end = i;
				if (ft_block_add_to_list(&block, &g_start_list) == OUT)
					return (OUT);
				block.start = i + 1;
			}
		}
	}
	return (ft_check_is_heredoc(OUT));
}
