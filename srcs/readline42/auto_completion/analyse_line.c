/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 18:24:47 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/23 16:33:48 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

char				*get_techline_compl(char *complete, size_t len)
{
	char			*tech_line;
	size_t			i;

	if (!complete || complete[0] == 0)
		return (NULL);
	tech_line = (char*)ft_xmalloc(len);
	i = 0;
	while (g_rline.cmd[i] && i < len)
	{
		tech_line[i] = get_tech_num(g_rline.cmd[i]);
		i++;
	}
	return (tech_line);
}

int					analyse_techline_compl(char *compl, char *tech,
						size_t len, int *pool)
{
	size_t			i;

	if (!(g_rline.cmd[g_rline.pos] == 0 || g_rline.cmd[g_rline.pos] == ' '))
		return (0);
	i = len - 1;
	while (i > 0)
	{
		if (tech[i] == 0)
			i--;
		else
			break ;
	}
	if (tech[i] == SLASH || tech[i] == DQUOTE || tech[i] == SQUOTE ||
		tech[i] == CPAREN || tech[i] == OBRACKET || tech[i] == CBRACKET ||
		tech[i] == CBRACE || tech[i] == TILDA || tech[i] == GTHAN ||
		tech[i] == LTHAN || tech[i] == AST || tech[i] == EQUAL ||
		tech[i] == ENTER)
		return (0);
	else if (compl[i] == ':' || compl[i] == '#' || compl[i] == '@' ||
		compl[i] == '!' || compl[i] == '^' || compl[i] == '?' ||
		compl[i] == '-' || compl[i] == '+' || compl[i] == ',')
		return (0);
	i = route_to_first_pool(tech, i, pool);
	i = (*pool == 0) ? route_to_other_pools(tech, i, pool) : i;
	return (i + 1);
}

size_t				route_to_first_pool(char *tech, size_t i, int *pool)
{
	size_t			save_i;

	save_i = i;
	if ((tech[i] == OBRACE || tech[i] == OPAREN || tech[i] == SCOLON || 
		tech[i] == AND || tech[i] == PIPE) || i == 0)
	{
		*pool = 1;
		return (i + 1);
	}
	if (tech[i] == DOLLAR)
	{
		*pool = 2;
		return (i + 1);
	}
	while (i > 0 && tech[i] == SPACE)
		i--;
	if (tech[i] == OBRACE || tech[i] == OPAREN || tech[i] == SCOLON || 
		tech[i] == AND || tech[i] == PIPE || i == 0)
	{
		*pool = 1;
		return (save_i + 1);
	}
	return (save_i);
}

size_t				route_to_other_pools(char *tech, size_t i, int *pool)
{
	size_t			save_i;

	save_i = i;
	
	while (i > 0 && tech[i] == SPACE)
		i--;
	if (tech[i] != SPACE && tech[i] != ENTER)
	{
		*pool = 3;
		return (save_i + 1);
	}
	ft_putendl_fd("no pool", 1); //TODO cancel
	return (0);
}