/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 17:07:05 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/07 18:49:52 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

/*
** @num_space - counts on which line is space found
** @num_pos - counts on which line is position found
*/

int			cursor_till_word_begginning(void)
{
	size_t			i;
	unsigned int	num_space;
	unsigned int	num_pos;
	struct winsize	sz;

	i = g_rline.pos;
	ioctl(1, TIOCGWINSZ, &sz);
	while (g_rline.cmd[i] != ' ' && i != 0)
		i--;
	num_space = on_which_line(g_rline.prompt_len + i, sz.ws_col);
	// // if (g_rline.str_num > 1)
	// // {
	// // 	while (g_rline.pos + g_rline.prompt_len >= sz.ws_col * i)
	// // 		i++;
	// // }
	// printf("HERE %s\n", g_rline.cmd + i);
	return (0);
}

unsigned int		on_which_line(size_t cmd_pos, unsigned short col)
{
	unsigned int	i;

	i = 1;
	while (cmd_pos >= col * i)
		i++;
	return (i);
}