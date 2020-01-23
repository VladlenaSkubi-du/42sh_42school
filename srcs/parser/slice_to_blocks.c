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

#include "parser.h"

int	ft_block_start_fg(t_ltree *block)
{
	t_ltree	*sub;
	t_ltree	final;
	int		buf;
	int		out_flag;

	block->flags = 0;
	buf = 0;
	while ((sub = ft_find_logic(block, &final, &buf)))
	{
		out_flag = exec_init(sub);
		if (buf != 0)
		{
			block->end = buf;
			buf = 0;
		}
		if (out_flag != 0 && block->flags & LOG_AND)
			break ;
		if (out_flag == 0 && block->flags & LOG_OR)
			break ;
		block->start = sub->end + 1;
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
	char			flag;

	i = 0;
	flag = 0;
	block.start = 0;
	while (i <= g_techline.len)
	{
		if (g_techline.line[i] == 3 || g_cmd[i] == '\0')
		{
			block.end = i;
			ft_block_start_fg(&block);
			block.start = i + 1;
		}
		if (g_techline.line[i] == AND && g_techline.line[i + 1] != AND && \
			g_techline.line[i + 1] != GTHAN && g_techline.line[i + 1] != LTHAN && \
		 	g_techline.line[i - 1] != GTHAN && g_techline.line[i - 1] !=LTHAN)
		{
			block.end = i;
			ft_block_start_bg(&block);
			block.start = i + 1;
		}
		i++;
	}
	return (0);
}
