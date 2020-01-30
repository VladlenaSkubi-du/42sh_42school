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

int	ft_block_start_fg(t_ltree *block)
{
	t_ltree	*sub;
	t_ltree	final;
	int		out_flag;
	
	while ((sub = ft_find_logic(block, &final)))
	{
		out_flag = exec_init(sub);	
		if (out_flag != 0 && final.flags & LOG_AND)
			break ;
		if (out_flag == 0 && final.flags & LOG_OR)
			break ;
		block->start = final.end + 1;
		final.end = block->end;
		if (final.flags & LOG_AND || final.flags & LOG_OR)
			block->start += 2;
	}
	return (0);
}

int	ft_block_start_bg(t_ltree *block)
{
	// t_ltree	*sub;

	// while ((sub = ft_find_pipe(block, &final)))
	// {
	// 	//start in background
	// }
	return (0);
}

/*
** Fucntion slice command string to blocks and send it to execv
*/

int	ft_slice(void)
{
	t_ltree			block;
	size_t			i;

	i = 0;
	block.start = 0;
	block.flags = 0;
	while (i <= g_techline.len)
	{
		if (g_techline.line[i] == SCOLON || g_cmd[i] == '\0')
		{
			block.end = i;
			ft_block_start_fg(&block);
			block.start = i + 1;
		}
		if (g_techline.line[i] == AND && g_techline.line[i + 1] != AND && \
			g_techline.line[i - 1] != AND && \
			g_techline.line[i + 1] != GTHAN && g_techline.line[i + 1] != LTHAN && \
		 	g_techline.line[i - 1] != GTHAN && g_techline.line[i - 1] != LTHAN)
		{
			block.end = i;
			ft_block_start_bg(&block);
			block.start = i + 1;
		}
		i++;
	}
	return (0);
}
