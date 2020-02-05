/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice_to_blocks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:43:51 by rbednar           #+#    #+#             */
/*   Updated: 2020/01/23 17:43:51 by rbednar          ###   ########.fr       */
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
	int		out_flag;
	int		k;

	while ((sub = ft_find_logic(block, &final)))
	{
		k = -1;
		while (k++)
			final.fd[k] = k;
		ft_find_redirection(&final);
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
** Function start list commands
*/

// int	ft_block_start(t_list *list)
// {
// 	t_ltree	*sub;
// 	t_ltree	final;
// 	int		out_flag;
	
// 	while ( ))
// 	{
// 		out_flag = exec_init(sub);	
// 		if (out_flag != 0 && final.flags & LOG_AND)
// 			break ;
// 		if (out_flag == 0 && final.flags & LOG_OR)
// 			break ;
// 		block->start = final.end + 1;
// 		final.end = block->end;
// 		if (final.flags & LOG_AND || final.flags & LOG_OR)
// 			block->start += 2;
// 	}
// 	return (0);
// }

int		ft_slice_bg(size_t *i, t_ltree	*block, t_list **start_list)
{
	if (g_techline.line[*i] == AND && g_techline.line[*i + 1] != AND && \
		g_techline.line[*i - 1] != AND && \
		g_techline.line[*i + 1] != GTHAN && \
		g_techline.line[*i + 1] != LTHAN && \
		g_techline.line[*i - 1] != GTHAN && g_techline.line[*i - 1] != LTHAN)
	{
		block->end = *i;
		block->flags |= IS_BG;
		ft_block_add_to_list(block, start_list);
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

	i = 0;
	block.start = 0;
	block.flags = GR_START;
	start_list = NULL;
	while (i <= g_techline.len)
	{
		if (g_techline.line[i] == SCOLON || g_cmd[i] == '\0')
		{
			block.end = i;
			ft_block_add_to_list(&block, &start_list);
			block.start = i + 1;
		}
		ft_slice_bg(&i, &block, &start_list);
		i++;
	}
	return (0);
}
