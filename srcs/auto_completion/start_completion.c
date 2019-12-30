/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_completion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 15:27:02 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/30 17:25:50 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

/*
** @pool = pool of variables: binary-files ('b'), variables ('v'),
** arguments ('a'), comment ('c');
** @new_y - we count relatively to the position where the cmd-line ends
** how low we move the cursor while printing the possible completion variants
*/

int					auto_completion(void)
{
	size_t			len;
	size_t			pos_back;
	

	len = ft_strlen(g_rline.cmd);
	pos_back = g_rline.pos;
	if (g_rline.pos == 0)
		print_alphabet(len, pos_back, 'b');
	return (0);
}

int					print_menu(size_t len, size_t pos_back, char pool)
{
	// char			*comment;
	// size_t			len_comment;
	// unsigned short	len_x;
	// unsigned short	menu_lines_num;

	// comment = get_menu(pool);
	// len_comment = ft_strlen(comment);
	// position_relative(&len_x, 0, len);
	// position_cursor_for_menu(len);
	// menu_lines_num = len_comment / g_screen.ws_col + 1;
	// ft_putstr_fd(comment, 2);
	// position_cursor("ch", 0, len_x); //after printing the menu to len
	// position_cursor("UP", 0, menu_lines_num + 1); //after printing the menu to len
	// g_rline.pos = pos_back;
	// move_cursor_from_old_position(len, 'l'); //form len to the old position
	return (0);
}

char				*get_menu(char pool)
{
	char			*menu;

	if (pool == 'c')
	{
		menu = "Please, choose a letter.\nThere are too many binaries:\n"; //придумать, как возвращать алфавит
	}
	return (menu);
}

int					clean_menu(void)
{
	size_t			len;
	size_t			pos_back;

	len = ft_strlen(g_rline.cmd);
	pos_back = g_rline.pos;
	position_cursor_for_menu(len);
	putcap("cd");
	g_rline.pos = pos_back;
	move_cursor_from_old_position(len, 'l');
	return (0);
}