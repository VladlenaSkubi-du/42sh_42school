/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_start_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 18:13:02 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/04 13:46:32 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

void			init_dquote(void)
{
	g_dquote.cmd_buf = NULL;
	g_dquote.buf_len = 0;
	g_dquote.flag_esc = 0;
	g_dquote.flag_quote = 0;
	g_dquote.check = NULL;
}

/*
** @g_flag is needed to know how much time we ran back to readline to wait for
** the symbols to get out of it to parser 
*/

int				back_to_readline(void)
{
	if (g_techline.len == 1 && g_techline.line[g_techline.len - 1] == BSLASH)
	{
		if (escape_character() == OUT)
			return (OUT);
	}
	else if (g_techline.len > 1 && g_techline.line[g_techline.len - 1] == BSLASH
		&& g_techline.line[g_techline.len - 2] != BSLASH)
		if (escape_character() == OUT)
			return (OUT);
	if (dquote_character() == OUT)
		return (OUT);
	g_prompt.prompt_func = main_prompt;
	// free(g_buf_cmd);
	return (0);
}

int				escape_character(void)
{
	g_dquote.flag_esc += 1;
	if (g_dquote.flag_quote > 0) //TODO разобраться в пересечении
		return (0);
	if (g_dquote.buf_len == 0)
		g_dquote.cmd_buf = init_buffer_cmd(g_cmd_size, g_cmd, &g_dquote.buf_len);
	else
		g_dquote.cmd_buf = add_buffer_cmd(g_dquote.cmd_buf, g_cmd_size,
			g_cmd, &g_dquote.buf_len);
	clean_parser42();
	g_prompt.prompt_func = other_prompt;
	// if (interactive_shell())
	// 	exit(PARSER_ERROR); //TODO удалить
	return (OUT);
}

int				dquote_character(void)
{
	int			tmp;
	
	tmp = 0;
	if ((tmp = check_quotes(&g_dquote.flag_quote, &g_dquote.check)) == -1)
		return (dquote_character_open());
	if (tmp == 0 && g_dquote.cmd_buf)
		dquote_character_closed();
	(g_dquote.check != NULL) ? ft_clear_stack(&g_dquote.check) : 0;
	return (0);
}
