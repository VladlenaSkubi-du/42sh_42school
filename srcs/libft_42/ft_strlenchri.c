/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlenchri.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 15:19:53 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/21 15:59:46 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "libft_42.h"

size_t			ft_strlenchri(const char *s, char c)
{
	size_t		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}