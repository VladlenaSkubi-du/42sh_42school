/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 12:55:34 by sschmele          #+#    #+#             */
/*   Updated: 2020/05/23 19:34:01 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnstr(char const *s, int len)
{
	int i;

	i = 0;
	if (s)
	{
		while (i < len)
		{
			ft_putchar(s[i]);
			i++;
		}
	}
}
