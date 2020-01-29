/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 10:32:02 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/29 10:35:58 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "libft_42.h"

int					ft_push_stack(t_stack **head, int data)
{
	t_stack			*tmp;

	tmp = (t_stack*)ft_xmalloc(sizeof(t_stack));
	tmp->next = *head;
	tmp->data = data;
	*head = tmp;
	return (0);
}
