/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser42.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 19:19:56 by rbednar           #+#    #+#             */
/*   Updated: 2020/02/28 19:36:13 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

int		parser(char *line)
{
	if (g_prompt.prompt_func == main_prompt
		&& (line == NULL || line[0] == 0))
	{
		free(line);
		return (0);
	}
	g_cmd = line;
	g_cmd_size = ft_strlen(g_cmd);
	ft_get_techline(g_cmd, &g_techline);
	add_to_history(g_cmd);
	g_hist.counter = g_hist.last + 1;
	pars_lex_exec(0);
	return (0);
}

// static int			perform_assignment(size_t eq)
// {
// 	size_t			var;
// 	size_t			value;
// 	char			*find;

// 	var = eq - 1;
// 	value = eq + 1;
// 	while (var > 0 && ft_isalnum(g_cmd[var]))
// 		var--;
// 	while (value < g_cmd_size)
// 		value++;
// 	find = ft_strndup(g_cmd + var, eq);
// 	// printf("%zu - %zu - %zu\n", var, eq, value);
// 	find_assignment_in_variables(var, eq, value);
// 	free(find);
// 	return (0);
// }

// static int			castrated_parser(void)
// {
// 	size_t			i;
	
// 	i = 0;
// 	while (i < g_techline.len)
// 	{
// 		if (g_techline.line[i] == EQUAL)
// 		{
// 			if ((i > 0 && i + 1 <= g_cmd_size) &&
// 				ft_isalnum(g_cmd[i - 1]) && g_cmd[i + 1])
// 				perform_assignment(i);
// 			else
// 			{
// 				printf("Something wrong\n"); //TODO delete
// 				// error_handler(COMMAND_NOT_FOUND, "="); //TODO исправить и отправлять всю часть строки до разделителя
// 				return (0); //переставить код возврата
// 			}
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int		pars_lex_exec(int tmp)
{
	// castrated_parser(); //TODO delete
	if (g_prompt.prompt_func != heredoc_prompt)
		if (nullify(&g_techline.line, g_cmd_size) == OUT)
		{
			clean_parser42();
			return (0);
		}
	ft_slice_fg();
	clean_parser42();
	return (0);
}

/*
** Function to check if find char is in use or just text
*/

char	get_tech_num(char check)
{
	char	*base;
	int		i;

	base = " \\;&\"\'()[]{}$~|><*=\n#\t";
	i = 0;
	while (base[i])
	{
		if (base[i] == check)
		{
			if (i == 21)
				return (2);
			else			
				return (i + 2);
		}
		i++;
	}
	if (check == EOF)
		return (EOF);
	return (1);
}

int		ft_get_techline(char *cmd, t_tech *result)
{
	size_t	i;

	i = 0;
	result->line = (char *)ft_xmalloc(ft_strlen(cmd) + 1);
	while (cmd[i])
	{
		result->line[i] = get_tech_num(cmd[i]);
		i++;
	}
	result->len = i;
	result->alloc_size = i;
	return (0);
}

int		ltree_init(t_ltree *final)
{
	final->start = 0;
	final->end = 0;
	final->flags = 0;
	final->fd = NULL;
	final->token = NULL;
	final->envir = NULL;
	final->ar_v = NULL;
	final->err = NULL;
	final->err_i = 0;
	final->l_cmd = NULL;
	final->l_tline.line = NULL;
	return (0);
}