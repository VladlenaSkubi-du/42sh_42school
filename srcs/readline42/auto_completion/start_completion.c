/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_completion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 15:27:02 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/21 19:51:29 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

/*
** @g_tablevel is a counter according to that we complete this or that line
** from the g_menu
** @g_complete - is a string, according to which we search
** options for completion. Can be empty if TAB is pushed before any other key
** @g_menu - the full menu for completion, all the possible options
*/

size_t				g_tablevel;
char				*g_complete;
char				**g_menu;

char				*path_parse_compl(void)
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
** arguments (3), bell (nothing can be done - 0);
** @total = total number of options
** @max_len = maximal length of the option-string within the whole
** menu array - is needed for the buffer output part
** @tech_line = is needed for analysis of the g_complete string - 
** parsing of the g_complete string
** @delete = by each TAB a word-option is added to the 
** g_complete part. If this option does not taken by the user and
** the user pushes TAB to change the option - the old option should
** be deleted - as many symbols as in @delete variable
** If there are no options to be auto-completed, there is a bell.
*/

int					auto_completion(void)
{
	size_t			pos_back;
	size_t			total;
	int				max_len;
	char			*tech_line;

	pos_back = g_rline.pos;
	max_len = 0;
	if (!(g_rline.flag & TAB))
	{
		g_complete = fill_complete(pos_back);
		tech_line = get_techline_compl(g_complete, g_rline.pos);
		g_menu = route_menu_receipt(tech_line, pos_back, &total, &max_len);
		if (g_menu == NULL || g_menu[0] == 0)
		{
			free(g_complete);
			return (incorrect_sequence());
		}
		if (print_menu(pos_back, g_menu, total, max_len))
			return (0);
		g_rline.flag |= TAB;
		g_tablevel = 0;
	}
	else
	{
		g_tablevel++;
		//TODO подстановка слова
	}
	return (0);
}

/*
** If the @g_complete line is empty and @pool is 1, menu consists of all
** the binary-options found in the environmental variable PATH and
** in the internal list of builtin programs.
** If @g_complete is not empty and @pool is 1 - the function
** ft_path_pars returns only those options that match.
** The same principle for other pools.
*/

char				**route_menu_receipt(char *tech_line,
						size_t tech_len, size_t *total, int *max_len)
{
	char			**menu;
	int				pool;
	int				tmp;	

	if (tech_line == NULL)
		menu = ft_path_pars("", path_parse_compl(), total, max_len);
	else
	{
		if ((tmp = analyse_techline_compl(tech_line, tech_len, &pool)) == 0)
			return (NULL);
		if (pool == 1)
			menu = ft_path_pars(g_complete + tmp - 1,
				path_parse_compl(), total, max_len);
		else if (pool == 2)
			menu = get_variables(g_complete + tmp - 1, total, max_len);
		else
			menu = get_arguments(g_complete + tmp - 1, total, max_len);	
	}
	return (menu);
}

/*
** Here we take everything that is before the cursor in the string
** and analyse it after
*/

char				*fill_complete(size_t pos_back)
{
	size_t			beg_word;
	size_t			end_word;
	size_t			space;
	char			*tmp;
	char			*complete;

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
	complete = ft_strtrim(tmp);
	free(tmp);
	return (complete);
}

/*
** After any key except of TAB is pushed, the menu under the line
** is cleared
*/

int					check_menu(void)
{
	if (g_rline.flag & TAB)
	{
		if (g_rline.flag & MENU)
			clean_menu();
		free(g_complete);
		ft_arrdel(g_menu);
		g_rline.flag &= ~TAB;
		(g_rline.flag & MENU) ? g_rline.flag &= ~MENU : 0;
		g_tablevel = 0;
	}
	return (0);
}
