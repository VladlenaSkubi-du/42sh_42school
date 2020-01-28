/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 12:56:39 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/28 14:48:51 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "libft_42.h"

int			ft_strrchri(char *s, int c)
{
    int		i;
	char	*p;

	i = 0;
	p = 0;
	while (s[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (s[i] == c)
		{
			p = (char*)s + i;
			break ;
		}
		i--;
	}
	if (i == 0 && p == 0)
		return (-1);
	return (p - s);
}