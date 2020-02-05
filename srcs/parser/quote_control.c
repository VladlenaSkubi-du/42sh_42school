/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:28:46 by hshawand          #+#    #+#             */
/*   Updated: 2020/02/05 17:28:32 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

/*
** Dquote removed
** if (*ptr == 1 || *ptr == 3 || *ptr == 4 || *ptr == 9 || *ptr == 10
** || *ptr == 14 || *ptr == 15 || *ptr == 16 || *ptr == 17 || *ptr == 18)
*/

int		terminate(char *ptr)
{
	*ptr = 0;
	return (0);
}

int		nullify_dquotes(char **ptr, int *nullifier, t_stack **stack)
{
	if (*nullifier == DQUOTE && **ptr == DQUOTE && \
		(**ptr - 1) != BSLASH)
		*nullifier = ft_pop_stack(stack);
	else if (*nullifier == SQUOTE && **ptr == SQUOTE)
		*nullifier = ft_pop_stack(stack);
	else if (*nullifier == SQUOTE)
		terminate(*ptr);
	else if (*nullifier == DQUOTE && \
			((**ptr != DOLLAR && (**ptr - 1) != BSLASH) || \
			!((**ptr == OPAREN || **ptr == OBRACE) && \
			(**ptr - 1) == DOLLAR)))
		terminate(*ptr);
	else if (*nullifier != SQUOTE && **ptr == OPAREN)
		*nullifier = ft_push_stack(stack, OPAREN);
	else if (*nullifier == OPAREN && **ptr == CPAREN)
		*nullifier = ft_pop_stack(stack);
	else if (*nullifier != SQUOTE && **ptr == OBRACE)
		*nullifier = ft_push_stack(stack, OPAREN);
	else if (*nullifier == OPAREN && **ptr == CBRACE)
		*nullifier = ft_pop_stack(stack);
	return (0);
}

int		nullify(char *techline)
{
	char	*ptr;
	int		nullifier;
	size_t	count;
	t_stack	*stack;

	count = 0;
	nullifier = 0;
	ptr = techline;
	stack = ft_init_stack();
	while (count < g_cmd_size)
	{
		if (!nullifier)
		{
			if (*ptr == DQUOTE && (*ptr - 1) != BSLASH)
				nullifier = DQUOTE && ft_push_stack(&stack, DQUOTE);
			else if (*ptr == SQUOTE && (*ptr - 1) != BSLASH)
				nullifier = SQUOTE && ft_push_stack(&stack, SQUOTE);
		}
		else
			nullify_dquotes(&ptr, &nullifier, &stack);
		ptr++;
		count++;
	}
	return (nullifier ? -1 : 0);
}

// int		nullify_backslash(void) //обработка зануления
// {
// 	char	*ptr;
// 	char	nullifier;
// 	size_t	count;

// 	count = 0;
// 	nullifier = 0;
// 	ptr = g_techline.line;
// 	while (count < g_cmd_size)
// 	{
// 		else if ((nullifier == 1 && *ptr == DQUOTE) || \
// 				(nullifier == 2 && *ptr == SQUOTE))
// 			nullifier = 0;
// 		else if (nullifier == 2)
// 			terminate(ptr);
// 		else if (nullifier == 1 && (*ptr != DOLLAR || \
// 		!((*ptr == OPAREN || *ptr == OBRACE) && \
// 		g_techline.line[count - 1] == DOLLAR)))
// 			terminate(ptr);
// 		ptr++;
// 		count++;
// 	}
// 	return (nullifier ? -1 : 0);
// }
