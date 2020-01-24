/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_issign.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 17:09:13 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/24 13:31:50 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "libft_42.h"

int				ft_issign(char c)
{
	if (c == ' ' || c == '#' || c == '%' || c == '!' ||
		c == '@' || c == '"' || c == '\\' || c == '^' ||
		c == '*' || c == '(' || c == ')' || c == '=' ||
		c == '/' || c == '.' || c == '\'' || c == ':' ||
		c == '-' || c == '$' || c == '&' || c == '|' || c == ';' ||
		c == ',' || c == '[' || c == ']' || c == '{' || c == '}' ||
		c == '?')
		return (1);
	return (0);
}
