#include "shell42.h"
#include "parser.h"

static char	*g_sign[23] = {
	"\0", "\0", " ", "\\", ";", "&", "\"", "\'", "(", ")", "[", "]",
	"{", "}", "$", "~", "|", ">", "<", "*", "=", "\n", "#"};

int		nullify_error(t_stack **stack)
{
	if ((*stack)->data == DOLLAR)
			ft_pop_stack(stack);
		if ((*stack)->data == DQUOTE || (*stack)->data == SQUOTE)
			g_prompt.prompt_func = dquote_prompt;
		if ((*stack)->data == OPAREN)
			g_prompt.prompt_func = subshell_prompt;
		if ((*stack)->data == OBRACE)
			g_prompt.prompt_func = cursh_prompt;
		if ((*stack)->data == BSLASH)
			g_prompt.prompt_func = other_prompt;
		if (((*stack)->data == EOF || if_noninteractive()) &&
			g_prompt.prompt_func != heredoc_prompt)
		{
			g_prompt.prompt_func = main_prompt;
			error_handler(SYNTAX_ERROR | (ERR_SQUOTE << 9),
				g_sign[(*stack)->data]);
		}
		ft_clear_stack(stack);
		return (OUT);
}
