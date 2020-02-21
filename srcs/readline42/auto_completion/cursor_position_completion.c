/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_position_completion.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 16:51:01 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/21 12:25:12 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int					position_cursor_for_menu(size_t len)
{
	// size_t			pos_old;
	// int	end_x;

	// pos_old = g_rline.pos;
	// if (g_rline.pos == 0 && len == 0)
	// 	tputs(g_cap.sf, 1, printc);
	// else
	// {
	// 	g_rline.pos = len;
	// 	move_cursor_from_old_position(pos_old, 'r');
	// 	position_relative(&end_x, 0, g_rline.pos);
	// 	if (end_x < g_screen.ws_col)
	// 		tputs(g_cap.sf, 1, printc);
	// }
	return (0);
}

int					position_cursor_after_menu_back(int len_x,
						int buf_lines, size_t pos_back, size_t len)
{
	size_t			i;

	i = -1;
	position_cursor("ch", 0, len_x);
	while (++i < buf_lines)
		putcap("sr");
	g_rline.pos = pos_back;
	move_cursor_from_old_position(len, 'l');
	return (0);
}

/*
** It is not logical to put this function here but because of norm...
*/

char				**route_by_prompts(size_t *total, int *max_len)
{
	char			**menu;
	t_path			*root;

	if (g_prompt.prompt_func == main_prompt)
		menu = ft_path_pars("", path_parse_compl(), total, max_len);
	else
	{
		root = fill_tree_with_arguments("./", "", total);
		if (root == NULL)
			return (NULL);
		menu = ft_add_block(&root, *total, max_len);
		ft_path_free(&root);
	}
	return (menu);
}