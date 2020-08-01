/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing_ansi.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:45:38 by rbednar           #+#    #+#             */
/*   Updated: 2020/08/01 15:23:10 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

int		pre_parsing_ansi(int *i, t_ltree *sub)
{
	char	*end;
	char	*cmd;

	end = sub->l_tline.line;
	cmd = sub->l_cmd;
	while (end[*i] != SQUOTE)
	{
		if (cmd[*i] == '\\')
			ansi_table_check(&cmd[*i], i, sub);
		(*i)++;
	}
	return (0);
}

int		ansi_table_check(char *symbol, int *i, t_ltree *sub)
{
	if (symbol[1] == 'a')
		symbol[1] = '\a';
	else if (symbol[1] == 'b')
		symbol[1] = '\b';
	else if (symbol[1] == 'e' || symbol[1] == 'E')
		symbol[1] = '\e';
	else if (symbol[1] == 'f')
		symbol[1] = '\f';
	else if (symbol[1] == 'n')
		symbol[1] = '\n';
	else if (symbol[1] == 'r')
		symbol[1] = '\r';
	else if (symbol[1] == 't')
		symbol[1] = '\t';
	else if (symbol[1] == 'v')
		symbol[1] = '\v';
	else if (symbol[1] == '\'')
		symbol[1] = '\'';
	else if (symbol[1] == '\"')
		symbol[1] = '\"';
	else if (symbol[1] == '?')
		symbol[1] = '\?';
	else
		return (ansi_esc_symbols(symbol, i, sub));
	return (ft_reglue(i, 1, sub));
}

int		ansi_esc_symbols(char *symbol, int *i, t_ltree *sub)
{
	char	*nnn;
	int		nums;

	nums = 1;
	if (ft_isoctdigit(symbol[1]))
	{
		while (symbol[nums + 1] && ft_isoctdigit(symbol[nums + 1]) && nums <= 2)
			nums++;
		if ((nnn = ft_strndup(&symbol[1], nums)) != NULL)
		{
			ft_reglue(i, nums, sub);
			nums = ft_atoi_base(nnn, 8);
			free(nnn);
		}
		symbol[0] = nums;
		return (0);
	}
	else
		return (ansi_esc_hex_symbols(symbol, i, sub));
}

int		ansi_esc_hex_symbols(char *symbol, int *i, t_ltree *sub)
{
	char	*nnn;
	int		nums;

	nums = 1;
	if (symbol[1] == 'x')
	{
		while (symbol[nums + 1] && ft_ishexdigit(symbol[nums + 1]) && nums <= 2)
			nums++;
		if (nums > 1)
			if ((nnn = ft_strndup(&symbol[2], nums - 1)) != NULL)
			{
				ft_reglue(i, nums, sub);
				nums = ft_atoi_base(nnn, 16);
				free(nnn);
			}
		symbol[0] = nums;
		return (0);
	}
	return (1);
}
