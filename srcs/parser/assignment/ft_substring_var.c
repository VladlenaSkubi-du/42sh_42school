/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substring_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 00:22:23 by rbednar           #+#    #+#             */
/*   Updated: 2020/03/03 01:50:40 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

/*
** Function finds and substitudes classic vars of type "${#parameter}"
*/

int		ft_substring_len(t_ltree *sub, char *find, char *oper, size_t *i)
{
	return (0);
}

/*
** Function finds and substitudes classic vars of types
** ${parameter#[word]} and ${parameter##[word]}
*/

int		ft_substring_s_l_prefix(t_ltree *sub, char *find, char *oper, size_t *i)
{
	int		s_l;
	
	s_l = (oper[1] == '#') ? LARGE : SMALL;
	
	
	return (0);
}

/*
** Function finds and substitudes classic vars of types
** ${parameter%[word]} and ${parameter%%[word]}
*/

int		ft_substring_s_l_suffix(t_ltree *sub, char *find, char *oper, size_t *i)
{
	int		s_l;
	
	s_l = (oper[1] == '%') ? LARGE : SMALL;
	
	return (0);
}