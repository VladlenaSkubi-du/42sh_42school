/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrshift.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 19:35:01 by vladlenasku       #+#    #+#             */
/*   Updated: 2020/05/23 20:20:37 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @arr should have enough space for positive shift
** If you need to add 3 str after the 2nd str (after 'b-str'):
** arr = "abcdef0000" - is the buffer (len 10) with some content
**        abcdef
** where each str goes down
** ft_arrshift(arr + 2, 3)
** Result: arr = "ab000cdef0"
**                ab   cdef
**
** If you neew to delete 3 str before d-str:
** arr = "abcdef0000" - is the buffer (len 10) with some content
**        abcdef
** ft_arrshift(arr + 3, -3)
** Result: arr = "def0000000"
**                def
**
** If you neew to delete d-str:
** arr = "abcdef0000" - is the buffer (len 10) with some content
**        abcdef
** ft_arrshift(arr + 3, -3)
** Result: arr = "abcef00000"
**                abcef
**
** THERE IS NO "PROTECTION" for the negative shift - should be done
** from the function that calls
*/

void			ft_arrshift(char **arr, size_t size, size_t shift)
{
	char		**buff;
	int			i;

	if (arr == (char**)NULL || arr[0] == (char*)NULL)
		return ;
	buff = (char**)ft_xmalloc(sizeof(char*) * (size + 1));
	ft_memcpy(buff, arr, sizeof(char*) * size);
	ft_memcpy(arr + shift, buff, sizeof(char*) * (size - shift));
	i = 0;
	while (i < (int)shift)
	{
		arr[i] = (char*)NULL;
		i++;
	}
	free(buff);
}