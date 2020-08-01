/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_processing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 16:09:23 by rbednar           #+#    #+#             */
/*   Updated: 2020/08/01 15:23:10 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

int			shift_cmd_substitution(char **lcmd, int start,
				int end, int len_subst)
{
	int		len_lcmd;
	int		shift;

	len_lcmd = ft_strlen(*lcmd);
	shift = len_subst - (end - start);
	if (end - start < len_subst)
	{
		*lcmd = ft_realloc(*lcmd, len_lcmd,
			len_lcmd + 1, len_lcmd + 1 + shift);
		ft_strshift(*lcmd + start, shift);
	}
	else if (end - start > len_subst)
		ft_strshift(*lcmd + start - shift, shift);
	return (0);
}

int			shift_techline_substitution(t_tech *tline, int start,
				int end, int len_subst)
{
	int			shift;

	shift = len_subst - (end - start);
	if (end - start < len_subst &&
			tline->alloc_size - tline->len - 1 < (size_t)len_subst)
	{
		tline->line = ft_realloc(tline->line, tline->len,
			tline->alloc_size, tline->alloc_size + len_subst);
		tline->alloc_size += len_subst;
		ft_strshift(tline->line + start, shift);
		tline->len += shift;
	}
	if (end - start > len_subst)
	{
		ft_strshift(tline->line + start - shift, shift);
		tline->len -= shift;
	}
	return (0);
}

void		clear_techline(t_tech *techline)
{
	free(techline->line);
	techline->line = NULL;
	techline->len = 0;
	techline->alloc_size = 0;
}
