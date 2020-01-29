/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 10:31:19 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/29 10:37:05 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "libft_42.h"

t_stack				*ft_init_stack(void)
{
	t_stack			*stack;

	stack = ft_xmalloc(sizeof(t_stack));
	stack->data = 0;
	stack->next = NULL;
}
