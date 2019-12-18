/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xmalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 19:37:01 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/18 18:23:18 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_42sh.h"

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
