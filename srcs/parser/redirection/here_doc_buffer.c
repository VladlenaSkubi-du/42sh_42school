/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_buffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 12:26:58 by rbednar           #+#    #+#             */
/*   Updated: 2020/02/19 16:53:26 by rbednar          ###   ########.fr       */
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

int		add_line_to_heredoc_fd(char *line_in, int fd)
{
	int		len;

	len = ft_strlen(line_in);
	if (line_in[len - 2] == '\\' && line_in[len - 1] == '\n')
	{
		line_in[len - 2] = '\0';
		line_in[len - 1] = '\0';
	}
	ft_putstr_fd(line_in, fd);
	return (0);
}

int		recover_g_cmd_here(void)
{
	clean_parser42();
	g_cmd = ft_strdup(g_heredoc.g_cmd_copy);
	g_cmd_size = g_heredoc.g_len_copy;
	g_techline.line = ft_strdup(g_heredoc.g_cmd_copy);
	g_techline.len = g_heredoc.g_len_copy;
	g_techline.alloc_size = g_heredoc.g_len_copy;
	return (0);
}