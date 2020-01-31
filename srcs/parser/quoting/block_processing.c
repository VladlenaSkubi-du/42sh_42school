/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 14:24:54 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/31 19:55:30 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

int				dquote_character_open(void)
{
	if (g_dquote.buf_len == 0)
		g_dquote.cmd_buf = init_buffer_cmd(g_cmd_size, g_cmd, &g_dquote.buf_len);
	else
		g_dquote.cmd_buf = add_buffer_cmd(g_dquote.cmd_buf, g_cmd_size,
			g_cmd, &g_dquote.buf_len);
	clean_parser42();
	g_prompt.prompt_func = dquote_prompt;
	// if (interactive_shell())
	// 	exit(PARSER_ERROR); //TODO удалить
	return (OUT);
}

int				dquote_character_closed(void)
{
	g_dquote.cmd_buf = add_buffer_last(g_dquote.cmd_buf, g_cmd_size,
		g_cmd, &g_dquote.buf_len);
	if (g_dquote.flag_esc > 0 && g_prompt.prompt_func == dquote_prompt)
		clear_cmd_from_slash(1);
	else if (g_dquote.flag_esc > 0 && g_prompt.prompt_func == other_prompt)
		clear_cmd_from_slash(2);
	else
	{
		clean_parser42();
		g_cmd = g_dquote.cmd_buf;
		g_cmd_size = g_dquote.buf_len;
		ft_get_techline();
	}
	g_dquote.flag_quote = 0;
	return (0);
}

int				clear_cmd_from_slash(int flag)
{
	clean_parser42();
	g_cmd = (char*)ft_xmalloc(g_dquote.buf_len -
		(flag * (g_dquote.flag_esc)) + g_cmd_size + 1);
	g_dquote.flag_esc = 0;
	g_cmd = copy_without_slash_enter(g_cmd, g_dquote.cmd_buf,
		&g_cmd_size, flag);
	ft_get_techline();
	free(g_dquote.cmd_buf);
	return (0);
}

char			*copy_without_slash_enter(char *cmd, char *buf_cmd,
					size_t *cmd_len, int sl_en)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (buf_cmd[i])
	{
		if (sl_en == 1 && (buf_cmd[i] == '\\' && buf_cmd[i + 1] == '\n'))
			i += 2;
		else if (sl_en == 2 && ((buf_cmd[i] == '\\' &&
			buf_cmd[i + 1] == '\n') || buf_cmd[i] == '\n'))
			i++;
		else
		{
			cmd[j] = buf_cmd[i];
			i++;
			j++;
		}
	}
	cmd[j] = '\0';
	*cmd_len = j;
	return (cmd);
}

int				check_quotes(int *flag_quotes, t_stack **check)
{
	size_t		i;

	if (*flag_quotes == 0)
	{
		*check = ft_init_stack();
		*flag_quotes = 1;
	}
	i = 0;
	while (i < g_techline.len)
	{
		if (g_techline.line[i] == SQUOTE && (*check)->data != SQUOTE)
			ft_push_stack(check, SQUOTE);
		else if (g_techline.line[i] == SQUOTE && (*check)->data == SQUOTE)
			ft_pop_stack(check);
		if (g_techline.line[i] == DQUOTE && (*check)->data != DQUOTE)
			ft_push_stack(check, DQUOTE);
		else if (g_techline.line[i] == DQUOTE && (*check)->data == DQUOTE)
			ft_pop_stack(check);
		i++;
	}
	if ((*check)->data != 0)
		return (-1);
	return (0);
}
