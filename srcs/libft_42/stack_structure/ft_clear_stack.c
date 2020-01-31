/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_stack.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 10:37:08 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/31 19:51:14 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "libft_42.h"

void			ft_clear_stack(t_stack **head)
{
	t_stack		*tmp;

	if ((*head)->next == NULL)
	{
		free(*head);
		*head = NULL;
	}
	while (*head)
	{
		tmp = *head;
		free(tmp);
		*head = (*head)->next;
	}
	*head = NULL;
}
