/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_completion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 15:27:02 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/18 21:06:30 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

size_t				g_tablevel;
char				*g_complete;

static char			*path_parse(void)
{
	size_t			i;

	i = 0;
	while (g_env[i])
	{
		if (ft_strncmp(g_env[i], "PATH=", 5) == 0)
			return (g_env[i] + 5);
		i++;
	}
	return (NULL);
}

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
	char			*tech_line;
	int				pool;
	char			**menu;
	size_t			tmp;
	size_t			i;

	pos_back = g_rline.pos;
	i = 0;
	if (!(g_rline.flag & TAB))
	{
		fill_complete(pos_back);
		tech_line = get_techline_compl(g_complete, g_rline.pos);
		if (tech_line == NULL)
			menu = ft_path_pars("", path_parse(), &tmp);
		else
		{
			if ((tmp = analyse_techline_compl(tech_line, pos_back, &pool)) == 0)
				return (incorrect_sequence());
			// printf("%s - %s\n", g_complete + tmp - 1, path_parse());
			menu = ft_path_pars(g_complete + tmp - 1, path_parse(), &tmp);
		}
		printf("\n%zu\n", tmp);
		while (i < tmp)
		{
			ft_putendl(menu[i]);
			i++;
		}
	}
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
	if (!ft_isalnum(g_rline.cmd[beg_word]) && beg_word > 0
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
		free(g_complete);
		// clean_menu();
		g_rline.flag &= ~TAB;
	}
	return (0);
}
