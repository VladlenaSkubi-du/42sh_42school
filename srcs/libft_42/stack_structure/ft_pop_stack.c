/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pop_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 10:19:52 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/05 13:09:44 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "libft_42.h"

int				ft_pop_stack(t_stack **head)
{
	int			res;
	t_stack		*tmp;

	tmp = *head;
	if ((*head)->next)
		*head = (*head)->next;
	else
		return (0);
	res = tmp->data;
	free(tmp);
	return (res);
}
