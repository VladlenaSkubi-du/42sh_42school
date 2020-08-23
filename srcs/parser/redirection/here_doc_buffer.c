/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_buffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:55:16 by rbednar           #+#    #+#             */
/*   Updated: 2020/08/23 17:25:22 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

int		add_to_heredoc_buf(char ***array, char *add, int *buf_size)
{
	int	i;

	i = 0;
	while ((*array)[i])
		i++;
	if (i == *buf_size)
	{
		ft_realloc_array(array, *buf_size, *buf_size + HEREDOC_BUF);
		*buf_size += HEREDOC_BUF;
	}
	(*array)[i] = ft_strdup(add);
	return (0);
}

/*
** It finds all typs of substitution
** '~'(tilda), $WORD, ${parameter}, $(command) for heredoc
*/

int		ft_sub_heredoc(t_ltree *sub)
{
	int	err;

	err = 1;
	while (err)
	{
		ft_find_tilda(sub, LINE);
		ft_find_var(sub);
		if ((err = ft_find_curv_var(sub)) & ERR_OUT)
			break ;
		err = 0;
	}
	return (err);
}

/*
** Function remove "\\n" and and find substitutions
*/

int		null_here_line(void)
{
	t_ltree *buf;

	buf = (t_ltree *)ft_xmalloc(sizeof(t_ltree));
	ltree_init(buf);
	buf->l_cmd = ft_strdup(g_cmd);
	ft_get_techline(buf->l_cmd, &buf->l_tline);
	buf->end = buf->l_tline.len;
	nullify(&buf->l_tline.line, buf->l_tline.len);
	buf->err_i = -1;
	while (++(buf->err_i) < buf->l_tline.len)
		pre_parsing_back((int*)&(buf->err_i), buf);
	ft_sub_heredoc(buf);
	free(g_cmd);
	g_cmd = buf->l_cmd;
	buf->l_cmd = NULL;
	ft_one_ltree_clear(buf);
	g_prompt.prompt_func = heredoc_prompt;
	add_to_heredoc_buf(&g_heredoc.buf, g_cmd, &g_heredoc.buf_size);
	return (0);
}

int		recover_g_cmd_here(void)
{
	clean_parser42();
	g_cmd = ft_strdup(g_heredoc.g_cmd_copy);
	g_techline.line = ft_strdup(g_heredoc.g_cmd_copy);
	g_techline.len = g_heredoc.len_copy;
	g_techline.alloc_size = g_heredoc.len_copy;
	return (0);
}

int		here_tab_remove(char **line)
{
	size_t	len;

	len = ft_strlen(*line);
	while ((*line)[0] == '\t')
	{
		ft_memmove(&(line[0]), &(line[1]), len);
		len--;
	}
	return (0);
}
