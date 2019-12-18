/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_issign.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 17:09:13 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/18 18:19:58 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int				ft_issign(char c)
{
	if (c == ' ' || c == '#' || c == '%' || c == '!' ||
		c == '@' || c == '"' || c == '\\' || c == '^' ||
		c == '*' || c == '(' || c == ')' || c == '=' ||
		c == '/' || c == '.' || c == '\'' || c == ':' ||
		c == '-' || c == '$')
		return (1);
	return (0);
}
