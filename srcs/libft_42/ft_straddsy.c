/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_straddsy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 20:11:14 by vladlenasku       #+#    #+#             */
/*   Updated: 2020/01/15 20:50:20 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_42.h"

char		*ft_straddsy(char *dest, char sy)
{
	int		i;

	i = 0;
	while (dest[i])
		i++;
	dest[i] = sy;
	return (dest);
}