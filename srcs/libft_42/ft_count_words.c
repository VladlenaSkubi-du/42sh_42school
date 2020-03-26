/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 22:55:13 by rbednar           #+#    #+#             */
/*   Updated: 2020/03/26 22:16:09 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "libft_42.h"

size_t	ft_count_words(char const *s, char c, size_t len)
{
	size_t	k;
	size_t	i;

	k = 0;
	i = 0;
	while (i < len)
	{
		if (s[i] != c && (s[i + 1] == c || i + 1 == len))
			k++;
		i++;
	}
	return (k);
}
