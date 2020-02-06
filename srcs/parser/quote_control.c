/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:28:46 by hshawand          #+#    #+#             */
/*   Updated: 2020/02/06 19:49:17 by rbednar          ###   ########.fr       */
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

/*
** Function needs to nullify symbols in comments and check if is EOF at end
*/

int		nullify_comment(char **ptr, int *nullifier, t_stack **stack)
{
	if ((**ptr == COMENT && *nullifier != SQUOTE && *nullifier != OBRACE && \
		*nullifier != DQUOTE) || (*nullifier == COMENT && **ptr != ENTER))
	{
		**ptr = SPACE;
		if (*nullifier != COMENT)
			!(ft_push_stack(stack, COMENT)) ? *nullifier = COMENT : 0;
	}
	if (*nullifier == COMENT && **ptr == ENTER)
		*nullifier = ft_pop_stack(stack);
	if (**ptr == EOF)
		!(ft_push_stack(stack, EOF)) ? *nullifier = EOF : 0;
	return (0);
}

int		nullify_backslash(char **ptr, int *nullifier)
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
			((**ptr != DOLLAR && *(*ptr - 1) != BSLASH) && \
			!((**ptr == OPAREN || **ptr == OBRACE) && \
			*(*ptr - 1) == DOLLAR)))
		terminate(*ptr);
	else if (*nullifier != SQUOTE && **ptr == OPAREN)
		!(ft_push_stack(stack, OPAREN)) ? *nullifier = OPAREN : 0;
	else if (*nullifier == OPAREN && **ptr == CPAREN)
		*nullifier = ft_pop_stack(stack);
	else if (*nullifier != SQUOTE && **ptr == OBRACE)
		!(ft_push_stack(stack, OBRACE)) ? *nullifier = OBRACE : 0;
	else if (*nullifier == OBRACE && **ptr == CBRACE)
		*nullifier = ft_pop_stack(stack);
	nullify_backslash(ptr, nullifier);
	nullify_comment(ptr, nullifier, stack);
	return (0);
}

int		nullify_promt_check(t_stack	**stack)
{
	char	*tmp;

	tmp = NULL;
	if ((*stack)->data != 0)
		{
			if ((*stack)->data == DQUOTE || (*stack)->data == SQUOTE)
				g_prompt.prompt_func = dquote_prompt;
			if ((*stack)->data == OPAREN)
				g_prompt.prompt_func = subshell_prompt;
			if ((*stack)->data == OBRACE)
				g_prompt.prompt_func = cursh_prompt;
			if ((*stack)->data == EOF)
			{
				g_prompt.prompt_func = main_prompt;
				tmp = ft_strndup(g_cmd, g_cmd_size - 1);
				free(g_cmd);
				g_cmd = tmp;
				g_cmd_size--;
				tmp = ft_strndup(g_techline.line, g_cmd_size);
				free(g_techline.line);
				g_techline.line = tmp;
				g_techline.len = g_cmd_size;
			}	
		}
		else
			g_prompt.prompt_func = main_prompt;
	ft_clear_stack(stack);
}

/*
** Function to check quotes " ", ' ' and send to null
** symbols between them in techline
** also it send line to check brackets ( ) or { }
** If it needs, doing return to Readline module to close
** brackets or quotes
*/

int		nullify(char **techline, size_t cmd_size)
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
				!(ft_push_stack(&stack, DQUOTE)) ? nullifier = DQUOTE : 0;
			else if (*ptr == SQUOTE && (*ptr - 1) != BSLASH)
				!(ft_push_stack(&stack, SQUOTE)) ? nullifier = SQUOTE : 0;
		}
		else
			nullify_dquotes(&ptr, &nullifier, &stack);
		ptr++;
		count++;
	}
	
	return (nullifier ? -1 : 0);
}
