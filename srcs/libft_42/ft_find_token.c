/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 23:49:50 by rbednar           #+#    #+#             */
/*   Updated: 2020/02/27 01:55:05 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_42.h"

static char    *ft_find_token_sep_one(char *str)
{
	if (!ft_strncmp(str, ";", 1))
		return(ft_strndup(";", 1));
	if (!ft_strncmp(str, "&", 1))
		return(ft_strndup("&", 1));
	if (!ft_strncmp(str, ";", 1))
		return(ft_strndup(";", 1));
	if (!ft_strncmp(str, "|", 1))
		return(ft_strndup("|", 1));
	if (!ft_strncmp(str, "(", 1))
		return(ft_strndup("(", 1));
	if (!ft_strncmp(str, ")", 1))
		return(ft_strndup(")", 1));
	if (!ft_strncmp(str, ">", 1))
		return(ft_strndup(">", 1));
	if (!ft_strncmp(str, "<", 1))
		return(ft_strndup("<", 1));
	return (NULL);
}

char    *ft_find_token_sep(char *str)
{
	if (!ft_strncmp(str, "&&", 2))
		return(ft_strndup("&&", 2));
	else if (!ft_strncmp(str, "||", 2))
		return(ft_strndup("||", 2));
	else if (!ft_strncmp(str, ";;", 2))
		return(ft_strndup(";;", 2));
	else if (!ft_strncmp(str, "<<", 2))
		return(ft_strndup("<<", 2));
	else if (!ft_strncmp(str, ">>", 2))
		return(ft_strndup(">>", 2));
	else if (!ft_strncmp(str, "<&", 2))
		return(ft_strndup("<&", 2));
	else if (!ft_strncmp(str, ">&", 2))
		return(ft_strndup(">&", 2));
	else if (!ft_strncmp(str, "<<-", 3))
		return(ft_strndup("<<-", 3));
	else
		return (ft_find_token_sep_one(str));
}
