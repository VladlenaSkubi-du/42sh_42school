/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:28:46 by hshawand          #+#    #+#             */
/*   Updated: 2020/02/05 20:05:57 by rbednar          ###   ########.fr       */
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

int		nullify_backslash(char **ptr, int *nullifier) //обработка зануления
{
	if ((*nullifier == 0 || *nullifier == DQUOTE) \
		&& **ptr == BSLASH)
		terminate(&ptr[0][1]);
	return (0);
}

/*
** Function to null symbols in techline between " ", or ' '
** also it send line to check brackets ( ) or { }
*/

int		nullify_dquotes(char **ptr, int *nullifier, t_stack **stack)
{
	if (*nullifier == DQUOTE && **ptr == DQUOTE && \
		*(*ptr - 1) != BSLASH)
		*nullifier = ft_pop_stack(stack);
	else if (*nullifier == SQUOTE && **ptr == SQUOTE)
		*nullifier = ft_pop_stack(stack);
	else if (*nullifier == SQUOTE)
		terminate(*ptr);
	else if (*nullifier == DQUOTE && \
			((**ptr != DOLLAR && *(*ptr - 1) != BSLASH) || \
			!((**ptr == OPAREN || **ptr == OBRACE) && \
			*(*ptr - 1) == DOLLAR)))
		terminate(*ptr);
	else if (*nullifier != SQUOTE && **ptr == OPAREN)
		*nullifier = ft_push_stack(stack, OPAREN);
	else if (*nullifier == OPAREN && **ptr == CPAREN)
		*nullifier = ft_pop_stack(stack);
	else if (*nullifier != SQUOTE && **ptr == OBRACE)
		*nullifier = ft_push_stack(stack, OBRACE);
	else if (*nullifier == OBRACE && **ptr == CBRACE)
		*nullifier = ft_pop_stack(stack);
	return (0);
}

/*
** Function to check quotes " ", ' ' and send to null
** symbols between them in techline
** also it send line to check brackets ( ) or { }
** If it needs, doing return to Readline module to close
** brackets or quotes
*/

int		nullify(char **techline, size_t cmd_size) //занулить все после # - коммент
{
	char	*ptr;
	int		nullifier;
	size_t	count;
	t_stack	*stack;

	count = 0;
	nullifier = 0;
	ptr = *techline;
	stack = ft_init_stack();
	while (count < cmd_size)
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
		count++
	}
	if (stack->data != 0)
	{
		if (stack->data == DQUOTE || stack->data == SQUOTE)
			g_prompt.prompt_func = dquote_prompt;
		if (stack->data == OPAREN)
			g_prompt.prompt_func = subshell_prompt;
		if (stack->data == OBRACE)
			g_prompt.prompt_func = cursh_prompt;		
	}
	else
		g_prompt.prompt_func = main_prompt;	
	return (nullifier ? -1 : 0);
}
