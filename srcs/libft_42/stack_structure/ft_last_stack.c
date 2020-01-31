/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_last_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 17:00:43 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/31 17:41:40 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "libft_42.h"

int				ft_last_stack(t_stack **head)
{
	t_stack		*tmp;	
	tmp = *head;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp->data);
}
