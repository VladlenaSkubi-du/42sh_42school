/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_start_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 18:13:02 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/30 15:26:39 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

/*
** @g_flag is needed to know how much time we ran back to readline to wait for
** the symbols to get out of it to parser 
*/

char            *g_buf_cmd;
size_t          g_len_buf_cmd;
int				g_flag;

int             back_to_readline(void)
{
	if (g_prompt.prompt_func == main_prompt)
	{
		g_buf_cmd = NULL;
		g_len_buf_cmd = 0;
		g_flag = 0;
	}
	if (g_techline.len == 1 && g_techline.line[g_techline.len - 1] == SLASH)
		escape_character();
	else if (g_techline.len > 1 && g_techline.line[g_techline.len - 1] == SLASH
		&& g_techline.line[g_techline.len - 2] != SLASH)
		escape_character();
	if (g_techline.line[0] == OPAREN || g_techline.line[0] == OBRACE)
		parenthesis_or_brace_subshell();
	if (g_flag > 0)
		clear_cmd_from_escape(g_flag);
	// printf("g_buf_cmd = %s - %zu\n", g_buf_cmd, g_len_buf_cmd);
	g_prompt.prompt_func = main_prompt;
	free(g_buf_cmd); //buf here we should send to the buffer and than to a file after the session
	return (0);
}

int				escape_character(void)
{
	g_flag += 1;
	if (g_len_buf_cmd == 0)
		g_buf_cmd = init_buffer_cmd(g_cmd_size, g_cmd, &g_len_buf_cmd);
	else
		g_buf_cmd = add_buffer_cmd(g_buf_cmd, g_cmd_size, g_cmd, &g_len_buf_cmd);
	clean_parser42();
	g_prompt.prompt_func = other_prompt;
	if (interactive_shell())
		exit(PARSER_ERROR); //TODO удалить
	return (0);
}

int				clear_cmd_from_escape(int flag)
{
	if (flag > 0)
	{
		g_buf_cmd = add_buffer_cmd(g_buf_cmd, g_cmd_size, g_cmd, &g_len_buf_cmd);
		clean_parser42();
		g_cmd = (char*)ft_xmalloc(g_len_buf_cmd - (2 * (g_flag)) + g_cmd_size + 1);
		g_flag = 0;
		g_cmd = copy_without_slash_enter(g_cmd, g_buf_cmd, &g_cmd_size);
		ft_get_techline();
	}
	else
	{
		g_cmd = (char*)ft_xmalloc(g_len_buf_cmd - 2 + 1);
		g_flag = 0;
		g_cmd = copy_without_slash_enter(g_cmd, g_buf_cmd, &g_cmd_size);
		g_cmd_size = ft_strlen(g_cmd);
		if (!g_cmd || g_cmd[0] == 0)
			btin_exit(SUCCESS);
	}
	return (0);
}

int				parenthesis_or_brace_subshell(void)
{
	return (0);
}