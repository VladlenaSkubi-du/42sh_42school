/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing_work.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 19:55:12 by rbednar           #+#    #+#             */
/*   Updated: 2020/02/20 17:14:39 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

/*
** Simle to remove unused number (num_sym) of symbols by moving end of g_cmd
** g_techline.line and resizing g_cmd_size and g_techline.len.
*/

int		ft_reglue(size_t *i, int num)
{
	size_t	z;
	size_t	size;

	ft_memmove(&g_cmd[*i], &g_cmd[*i + num], g_cmd_size - (*i + num - 1));
	g_cmd_size -= num;
	ft_memmove(&g_techline.line[*i], &g_techline.line[*i + num], \
	g_techline.len - (*i + num - 1));
	g_techline.len -= num;
	z = g_cmd_size;
	size = z + num;
	while (++z <= size)
	{
		g_cmd[z] = '\0';
		g_techline.line[z] = '\0';
	}
	return (0);
}

int		pre_parsing_back(size_t *i)
{
	char	*end;

	end = g_techline.line;
	if (end[*i] == BSLASH && end[*i + 1] == ENTER)
		ft_reglue(i, 2);
	if (end[*i] == BSLASH && end[*i + 1] == BSLASH)
	{
		ft_reglue(i, 1);
		(*i)++;
	}
	if (end[*i] == BSLASH)
		ft_reglue(i, 1);
	return (0);
}

int		pre_parsing_andor_pipe(size_t *i)
{
	char	*end;

	end = g_techline.line;
	if ((end[*i] == PIPE && end[*i + 1] == PIPE) ||
		(end[*i] == AND && end[*i + 1] == AND) ||
		end[*i] == PIPE)
	{
		if (end[*i] == PIPE && end[*i + 1] != PIPE)
			*i += 1;
		else
			*i += 2;		
		while (end[*i] == SPACE)
			(*i)++;
		if (end[*i] == ENTER)
		{
			end[*i] = SPACE;
			g_cmd[*i] = ' ';
		}
	}
	return (0);
}

int		pre_parsing_squote(size_t *i)
{
	char	*end;

	end = g_techline.line;
	if (end[*i] == SQUOTE)
	{
		ft_reglue(i, 1);
		while (end[*i] != SQUOTE)
			(*i)++;
		ft_reglue(i, 1);
	}
	pre_parsing_andor_pipe(i);
	pre_parsing_back(i);
	return (0);
}

/*
** This function and subfunctions needs to cut and glue line before parsing.
** It shall be done by POSIX to remove \, "" and '' from line
*/

int		pre_parsing_cut_glue(void)
{
	char	*end;
	size_t	i;

	i = 0;
	end = g_techline.line;
	while (i < g_cmd_size)
	{
		if (end[i] == DQUOTE)
		{
			ft_reglue(&i, 1);
			while (end[i] != DQUOTE)
			{
				end[i] == SPACE ? end[i] = GLUE : 0;
				pre_parsing_back(&i);
				i++;
			}
			ft_reglue(&i, 1);
		}
		else
			pre_parsing_squote(&i);
		if (end[i] == ENTER && (g_cmd_size - i) == 1)
			ft_reglue(&i,1);
		i++;
	}
	// printf("techline pre:");//печать для проверки
	// i = -1;
	// while (++i < g_techline.len)
	// 	printf("%3d", g_techline.line[i]);
	// printf("\n");
	// printf("g_cmd pre=%s\n", g_cmd);
	return (0);
}
