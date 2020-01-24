/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:56:18 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/24 13:31:50 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "libft_42.h"

void		*ft_realloc(void *subj, size_t len_subj,
				size_t len, size_t len_needed)
{
	void	*ptr;

	if (!(ptr = malloc(len_needed)))
	{
		write(2, "No space left\n", 15);
		exit(MALLOC_ERROR);
	}
	if (len_needed > len_subj)
	{
		ft_memcpy(ptr, subj, len);
		ft_bzero(ptr + len, len_needed - len);
	}
	else
		ft_memcpy(ptr, subj, len_needed);
	free(subj);
	return (ptr);
}
