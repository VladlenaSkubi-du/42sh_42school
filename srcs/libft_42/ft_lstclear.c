/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 22:45:34 by rbednar           #+#    #+#             */
/*   Updated: 2020/02/18 17:27:59 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_42.h"

void	ft_lstclear(t_list **begin_list)
{
	t_list *tmp;

	if (!(begin_list) || !(*begin_list))
		return ;
	while (*begin_list)
	{
		tmp = (*begin_list)->next;
		if ((*begin_list)->content)
			free((*begin_list)->content);
		free((*begin_list));
		*begin_list = tmp;
	}
	*begin_list = NULL;
}
