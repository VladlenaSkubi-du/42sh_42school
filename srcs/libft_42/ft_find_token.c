/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 23:49:50 by rbednar           #+#    #+#             */
/*   Updated: 2020/03/26 22:16:35 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "libft_42.h"

static char    *ft_find_token_sep_one(char *str)
{
	if (ft_strlen(str) > 0)
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
	}
	return (NULL);
}

char    *ft_find_token_sep(char *str)
{
	if (ft_strlen(str) > 1)
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
		else if (ft_strlen(str) > 2)
			if (!ft_strncmp(str, "<<-", 3))
				return(ft_strndup("<<-", 3));
	}
	return (ft_find_token_sep_one(str));
}
