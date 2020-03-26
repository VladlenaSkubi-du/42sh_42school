/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 19:09:42 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/26 22:17:17 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "libft.h"

t_list	*ft_lstlast(t_list **begin_list)
{
	t_list	*tmp;

	tmp = *begin_list;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
