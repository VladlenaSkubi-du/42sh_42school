/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_completion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 15:27:02 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/02 01:42:22 by vladlenasku      ###   ########.fr       */
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
		print_menu(len, pos_back, 'b');
	return (0);
}

static char			**get_menu(char pool, int *menu_lines)
{
	char			**menu;

	menu = (char**)ft_xmalloc((sizeof(char*) * (10 + 1)));// if (pool == 'c')
	menu[10] = 0;
	menu[0] = "la";
	menu[1] = "ls";
	menu[2] = "lp";
	menu[3] = "lo";
	menu[4] = "ll";
	menu[5] = "lk";
	menu[6] = "ly";
	menu[7] = "lg";
	menu[8] = "lw";
	menu[9] = "lh";
	*menu_lines = 10;
	// {
	// 	menu = "Please, choose a letter.\nThere are too many binaries:\n"; //придумать, как возвращать алфавит
	// }
	return (menu);
}

int					print_menu(size_t len, size_t pos_back, char pool)
{
	char			**menu;
	// size_t			len_comment;
	unsigned short	len_x;
	int				menu_lines_num;
	size_t			i;

	// comment = get_menu(pool);
	// len_comment = ft_strlen(comment);
	i = -1;
	position_relative(&len_x, 0, len);
	position_cursor_for_menu(len);
	menu = get_menu(pool, &menu_lines_num);
	// menu_lines_num = len_comment / g_screen.ws_col + 1;
	while (++i < 10)
		buffer_col_print(menu[i], 8, 10);
	i = 0;
	while (++i < 10)
		ft_putendl_fd(buffer[i], 1);
	position_cursor("ch", 0, len_x); //after printing the menu to len
	position_cursor("UP", 0, menu_lines_num + 1); //after printing the menu to len
	g_rline.pos = pos_back;
	move_cursor_from_old_position(len, 'l'); //form len to the old position
	return (0);
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