/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_start_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 18:13:02 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/29 14:25:16 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

char            *g_buf_cmd;
size_t          g_len_buf_cmd;
int				g_flag;

int             back_to_readline(void) //ctrl-C выходит из ридлайна в main, все при этом подчищая, ctrl-D выходит из шелла
{
	if (g_prompt.prompt_func == main_prompt)
	{
		g_buf_cmd = NULL;
		g_len_buf_cmd = 0;
		g_flag = 0;
	}
	if (g_techline.line[g_techline.len - 1] == SLASH)
		escape_character();
	if (g_flag > 0)
		clear_cmd_from_escape(&g_flag);
	// printf("g_buf_cmd = %s - %zu\n", g_buf_cmd, g_len_buf_cmd);
	g_prompt.prompt_func = main_prompt;
	return (0);
}

int			escape_character(void)
{
	g_flag += 1;
	if (g_len_buf_cmd == 0)
		g_buf_cmd = init_buffer_cmd(g_cmd_size, g_cmd, &g_len_buf_cmd);
	else
		g_buf_cmd = add_buffer_cmd(g_buf_cmd, g_cmd_size, g_cmd, &g_len_buf_cmd);
	g_prompt.prompt_func = other_prompt;
	if (interactive_shell())
		exit(PARSER_ERROR); //TODO удалить
	return (0);
}

int			clear_cmd_from_escape(int *flag)
{
	g_buf_cmd = add_buffer_cmd(g_buf_cmd, g_cmd_size, g_cmd, &g_len_buf_cmd);
	clean_parser42();
	g_cmd = (char*)ft_xmalloc(g_len_buf_cmd - (2 * (*flag)) + g_cmd_size);
	flag = 0;
	g_cmd = copy_without_slash_enter(g_cmd, g_buf_cmd, &g_len_buf_cmd);
	ft_get_techline();
	return (0);
}
