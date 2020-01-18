/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice_to_block.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 22:19:23 by rbednar           #+#    #+#             */
/*   Updated: 2019/12/19 22:19:23 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int			ft_block_start_fg(t_ltree *block)
{
	t_ltree	*sub;

	while ((sub = ft_find_spec(block)))
	{
		//start in foreground
	}
	return (0);
}

int			ft_block_start_bg(t_ltree *block)
{
	t_ltree	*sub;

	while ((sub = ft_find_spec(block)))
	{
		//start in background
	}
	return (0);
}

/*
**Fucntion slice command string to blocks and send it to execv
*/

int         ft_slice(void)
{
	t_ltree    block;
	size_t     i;
	char       flag;

	i = 0;
	flag = 0;
	block.start = 0;
	while (i <= g_techline->len)
	{
		if (g_techline->line[i] == 3 || g_cmd[i] == '\0')
		{
			block.end = i;
			ft_block_start_fg(&block);
			block.start = i + 1;
		}
		if (g_techline->line[i] == 4)
		{
			block.end = i;
			ft_block_start_bg(&block);
			block.start = i + 1;
		}
		i++;
	}
	return(0);
}