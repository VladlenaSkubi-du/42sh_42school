/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_completion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 15:27:02 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/17 15:49:47 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

char				*g_tablevel;
char				*g_complete;

/*
** @pool = pool of variables: binary-files (1), variables (2),
** arguments (3), comment (4), bell (nothing can be done - 0);
** @complete - is a string, according to which we search
** options for completion
** @tab_push is a counter according to that we complete this or that line
** from the menu
*/

int					auto_completion(void)
{
	size_t			pos_back;
	int				pool;

	pos_back = g_rline.pos;
	fill_complete(pos_back);
	g_rline.flag |= TAB;
	g_tablevel = 0;
	return (0);
}

int					fill_complete(size_t pos_back)
{
	size_t			beg_word;
	size_t			end_word;
	size_t			space;
	char			*tmp;

	beg_word = g_rline.pos;
	end_word = beg_word;
	if (!ft_isalnum(g_rline.cmd[beg_word]) && beg_word - 1 > 0
		&& ft_isalnum(g_rline.cmd[beg_word - 1]))
		beg_word--;
	while (beg_word > 0 && ft_isalnum(g_rline.cmd[beg_word]))
		beg_word--;
	while (g_rline.cmd[end_word] && end_word < g_rline.pos
		&& ft_isalnum(g_rline.cmd[end_word]))
		end_word++;
	space = beg_word;
	while (space > 0 && g_rline.cmd[space] == ' ')
		space--;
	tmp = ft_strndup(g_rline.cmd + beg_word, end_word - beg_word);
	g_complete = ft_strtrim(tmp);
	free(tmp);
	return (0);
}

int					check_menu(void) //поправить возврат после нажатия символа
{
	if (g_rline.flag & TAB)
	{
		// clean_menu();
		g_rline.flag &= ~TAB;
	}
	return (0);
}
