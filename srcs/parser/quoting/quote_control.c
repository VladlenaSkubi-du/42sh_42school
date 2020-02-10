/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:28:46 by hshawand          #+#    #+#             */
<<<<<<< HEAD:srcs/parser/quoting/quote_control.c
/*   Updated: 2020/02/10 19:56:59 by rbednar          ###   ########.fr       */
=======
/*   Updated: 2020/02/08 16:24:50 by sschmele         ###   ########.fr       */
>>>>>>> 86b5288a9249ee665eaaa5e7d4014d81c207bd07:srcs/parser/quote_control.c
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

char	*g_sign[22] = {
	"\0", " ", "\\", ";", "&", "\"", "\'", "(", ")", "[", "]",
	"{", "}", "$", "~", "|", ">", "<", "*", "=", "\n", "#"};

/*
** Dquote removed
** if (*ptr == 1 || *ptr == 3 || *ptr == 4 || *ptr == 9 || *ptr == 10
** || *ptr == 14 || *ptr == 15 || *ptr == 16 || *ptr == 17 || *ptr == 18)
*/

/*
** Function needs to nullify symbols in comments and check if is EOF at end
*/

int		nullify_comment(char **ptr, t_stack **stack)
{
	if ((**ptr == COMENT && (*stack)->data != SQUOTE && \
		(*stack)->data != OBRACE &&
		(*stack)->data != DQUOTE) || ((*stack)->data == COMENT && \
		**ptr != ENTER))
	{
		**ptr = SPACE;
		if ((*stack)->data != COMENT)
			ft_push_stack(stack, COMENT);
	}
	if ((*stack)->data == COMENT && **ptr == ENTER)
		ft_pop_stack(stack);
	if (**ptr == EOF)
		ft_push_stack(stack, EOF);
	return (0);
}

int		nullify_backslash(char **ptr, t_stack **stack,\
		size_t *count)
{
	if (((*stack)->data == 0 || (*stack)->data == DQUOTE) \
		&& **ptr == BSLASH && ptr[0][1] != ENTER)
	{
		**ptr = 0;
		ptr[0][1] = 0;
	}
	if ((*stack)->data == 0 \
		&& **ptr == BSLASH && ptr[0][1] == ENTER &&\
		(g_cmd_size - *count) == 2)
		ft_push_stack(stack, BSLASH);
	return (0);
}

/*
** Function to null symbols in techline between " ", or ' '
** also it send line to check brackets ( ) or { }
*/

int		nullify_dquotes(char **ptr, t_stack **stack,\
		size_t *count)
{
	if ((*stack)->data == DQUOTE && **ptr == DQUOTE && \
		*(*ptr - 1) != BSLASH)
		ft_pop_stack(stack);
	else if ((*stack)->data == SQUOTE && **ptr == SQUOTE)
		ft_pop_stack(stack);
	else if ((*stack)->data == SQUOTE && **ptr != EOF)
		**ptr = 0;
	else if ((*stack)->data == DQUOTE && \
			((**ptr != DOLLAR && *(*ptr - 1) != BSLASH) && \
			**ptr != EOF && **ptr != BSLASH && **ptr != ENTER &&\
			!((**ptr == OPAREN || **ptr == OBRACE) && \
			*(*ptr - 1) == DOLLAR)))
		**ptr = 0;
	else if ((*stack)->data != SQUOTE && **ptr == OPAREN)
		ft_push_stack(stack, OPAREN);
	else if ((*stack)->data == OPAREN && **ptr == CPAREN)
		ft_pop_stack(stack);
	else if ((*stack)->data != SQUOTE && **ptr == OBRACE)
		ft_push_stack(stack, OBRACE);
	else if ((*stack)->data == OBRACE && **ptr == CBRACE)
		ft_pop_stack(stack);
	return (0);
}

int		nullify_promt_check(t_stack **stack)
{
	if ((*stack)->data != 0)
	{
		if ((*stack)->data == DQUOTE || (*stack)->data == SQUOTE)
			g_prompt.prompt_func = dquote_prompt;
		if ((*stack)->data == OPAREN)
			g_prompt.prompt_func = subshell_prompt;
		if ((*stack)->data == OBRACE)
			g_prompt.prompt_func = cursh_prompt;
		if ((*stack)->data == BSLASH)
			g_prompt.prompt_func = other_prompt;
		if ((*stack)->data == EOF)
		{
			g_prompt.prompt_func = main_prompt; //можно вынести в отдельную функцию
			error_handler(SYNTAX_ERROR | (ERR_SQUOTE << 8),
				g_sign[(*stack)->next->data]);
		}
		return (OUT);
	}
	else
		g_prompt.prompt_func = main_prompt;
	ft_clear_stack(stack);
	return (0);
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
	size_t	count;
	t_stack	*stack;

	count = 0;
	ptr = *techline;
	stack = ft_init_stack();
	while (count < cmd_size)
	{
		if (!(stack->data))
		{
			if (*ptr == DQUOTE && (*ptr - 1) != BSLASH)
				ft_push_stack(&stack, DQUOTE);
			else if (*ptr == SQUOTE && (*ptr - 1) != BSLASH)
				ft_push_stack(&stack, SQUOTE);
		}
		else
			nullify_dquotes(&ptr, &stack, &count);
		nullify_backslash(&ptr, &stack, &count);
		nullify_comment(&ptr, &stack);
		ptr++;
		count++;
	}
<<<<<<< HEAD:srcs/parser/quoting/quote_control.c
	return (nullify_promt_check(&stack));
=======
	// printf("techline cur:");
	// count = -1;
	// while (++count < g_techline.len)
		// printf(" %d", g_techline.line[count]);
	// printf("\n");
	return (nullify_promt_check(&stack)); //нужно написать функцию для обработки строки перед отправкой в парсер
	// сделать Quote Removal
	//The quote characters ( <backslash>, single-quote, and double-quote) that were present in the original word shall be removed unless they have themselves been quoted.
	
>>>>>>> 86b5288a9249ee665eaaa5e7d4014d81c207bd07:srcs/parser/quote_control.c
}
	// printf("g_cmd nul=%s\n", g_cmd);//печать для проверки
	// printf("techline cur:");
	// count = -1;
	// while (++count < g_techline.len)
	// 	printf("%3d", g_techline.line[count]);
	// printf("\n");
	//нужно написать функцию для обработки строки перед отправкой в парсер
	// сделать Quote Removal
	//The quote characters ( <backslash>, single-quote, and double-quote) that were present in 
	//the original word shall be removed unless they have themselves been quoted.
