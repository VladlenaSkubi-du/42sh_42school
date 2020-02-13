/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser42.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 20:06:56 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/13 13:59:57 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

int					parser(char *line)
{
	if (g_prompt.prompt_func == main_prompt
		&& (line == NULL || line[0] == 0))
	{
		free(line);
		return (0);
	}
	g_cmd = line;
	g_cmd_size = ft_strlen(g_cmd);
	ft_get_techline();
	// if (back_to_readline() == OUT)
	// 	return (0);
	add_to_history(g_cmd);
	g_hist.counter = g_hist.last + 1;
	pars_lex_exec(0);
	return (0);
}

static int			perform_assignment(size_t eq)
{
	size_t			var;
	size_t			value;
	char			*find;

	var = eq - 1;
	value = eq + 1;
	while (var > 0 && ft_isalnum(g_cmd[var]))
		var--;
	while (value < g_cmd_size)
		value++;
	find = ft_strndup(g_cmd + var, eq);
	// printf("%zu - %zu - %zu\n", var, eq, value);
	find_assignment_in_variables(var, eq, value);
	free(find);
	return (0);
}

static int			castrated_parser(void)
{
	size_t			i;
	
	i = 0;
	while (i < g_techline.len)
	{
		if (g_techline.line[i] == EQUAL)
		{
			if ((i > 0 && i + 1 <= g_cmd_size) &&
				ft_isalnum(g_cmd[i - 1]) && g_cmd[i + 1])
				perform_assignment(i);
			else
			{
				printf("Something wrong\n"); //TODO delete
				// error_handler(COMMAND_NOT_FOUND, "="); //TODO исправить и отправлять всю часть строки до разделителя
				return (0); //переставить код возврата
			}
		}
		i++;
	}
	return (0);
}

int		pars_lex_exec(int tmp)
{
	castrated_parser();
	if (nullify(&g_techline.line, g_cmd_size) == OUT)
	{
		clean_parser42();
		return (0);
	}
	pre_parsing_cut_glue();
	// ft_putendl_fd(g_cmd, 1);
	// ft_slice_fg();
	clean_parser42();
	return (0);
}

/*
** Function to check if find char is in use or just text
*/

char	get_tech_num(char check)
{
	char	*base;
	size_t	i;

	base = " \\;&\"\'()[]{}$~|><*=\n#\t";
	i = 0;
	while (base[i])
	{
		if (base[i] == check)
		{
			if (i == 21)
				return (1);
			else			
				return (i + 1);
		}
		i++;
	}
	if (check == EOF)
		return (EOF);
	return (0);
}

int		ft_get_techline(void)
{
	size_t	i;

	i = 0;
	g_techline.line = (char *)ft_xmalloc(g_cmd_size + 1);
	while (g_cmd[i])
	{
		g_techline.line[i] = get_tech_num(g_cmd[i]);
		i++;
	}
	g_techline.len = i;
	g_techline.alloc_size = i;
	return (0);
}

/*
int	ft_backslash_find(char *start, char *str)
{
	if (str > start && *(str - 1) != '\\')
		return(0);
	else
		return(1);
}
*/
/*
** Parser function that gets **string from Readline or from argv
** and do tech line
*/
/*
int	ft_parser(char **str)
{
	char	*str_tech;
	char	*line;
	int		i;

	line = {' ', '\\', ';', '&', '\"','\'', '(', ')', '[', ']', '{', '}', '$', '~', '|', '>', '<', '*'};
	//		0	 1	   2	3	 4	  5		6	  7	   8	9	10	 11	  12   13   14   15   16   17
	if (!(str_tech = ft_strdup(*str)))
		return (1);
	i = 0;
	while (*str[i])
	{
		j = -1;
		while (++j < 19)
		{
			if (j != 18)
				if (str_tech[i] == line[j])
					str_tech[i] = j;
			else
					str_tech[i] = 0;
		}
		i++;
	}
}
*/
