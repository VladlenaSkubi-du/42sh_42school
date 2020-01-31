/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_stack.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 10:37:08 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/30 16:59:26 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "libft_42.h"

void			ft_clear_stack(t_stack **head)
{
	t_stack		*tmp;

	while (*head)
	{
		tmp = *head;
		free(tmp);
		*head = (*head)->next;
	}
	*head = NULL;
}