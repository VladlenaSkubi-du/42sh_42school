/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:32:06 by rbednar           #+#    #+#             */
/*   Updated: 2020/02/04 12:50:01 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_42.h"

void		add_list_to_end(t_list *start, t_list *new)
{
	t_list	*tmp;

	tmp = start;
	if (start && new)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
