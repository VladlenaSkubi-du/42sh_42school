/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdiff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 14:36:51 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/03 14:41:07 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "libft_42.h"

int		ft_strdiff(char const *s1, char const *s2)
{
	int i;

	if (s1 == 0 || s2 == 0)
		return (0);
	else if (*s1 == '\0' && *s2 == '\0')
		return (1);
	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (0);
	}
	if (s1[i] == '\0' && s2[i] != '\0')
		return (0);
	if (s1[i] != '\0' && s2[i] == '\0')
		return (0);
	return (1);
}
