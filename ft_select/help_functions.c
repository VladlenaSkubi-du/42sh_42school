/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:09:50 by sschmele          #+#    #+#             */
/*   Updated: 2019/11/19 16:39:01 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		*ft_xmalloc(size_t size)
{
	void	*ptr;

	if (!(ptr = malloc(size)))
	{
		write(STDERR_FILENO, "No space left\n", 15);
		exit(1);
	}
	ft_bzero(ptr, size);
	return (ptr);
}

char		*ft_straddsy(char *dest, char sy)
{
	int		i;

	i = 0;
	while (dest[i])
		i++;
	dest[i] = sy;
	return (dest);
}

int			ft_putint(int c)
{
	return (write(STDERR_FILENO, &c, 1));
}
