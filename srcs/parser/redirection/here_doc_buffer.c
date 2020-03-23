/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_buffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 12:26:58 by rbednar           #+#    #+#             */
/*   Updated: 2020/03/23 18:38:51 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

static const char	g_letters[] =
"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

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
** Function remove "\\n" and and find substitutions
*/

int		null_here_line(void)
{
	size_t	i;
	char	*tmp;

	i = -1;
	tmp = ft_parsing_str(g_cmd);
	g_prompt.prompt_func = heredoc_prompt;
	free(g_cmd);
	g_cmd = tmp;
	g_cmd_size = ft_strlen(g_cmd);
	while (++i <= g_cmd_size)
	{
		if (g_techline.line[i] == BSLASH && g_techline.line[i + 1] != ENTER)
			g_techline.line[i + 1] = TEXT;
	}
	if (g_cmd[g_cmd_size - 2] == '\\' && g_cmd[g_cmd_size - 1] == '\n')
	{
		g_cmd[g_cmd_size - 2] = '\0';
		g_cmd[g_cmd_size - 1] = '\0';
	}
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

/*
** Generate a temporary file name based on TMPL.  TMPL must match the
** rules for mk[s]temp (i.e. end in "XXXXXX").  The name constructed
** does not exist at the time of the call to mkstemp.  TMPL is
** overwritten with the result. Implementation of mkstemp by POSIX
*/

int		ft_tmpfile(char *tmpl)
{
	int		len;
	char	*tmp;
	char	*xxx;
	int		fd;
	int		buf;

	len = ft_strlen(tmpl);
	fd = -1;
	buf = 0;
	(tmp = ft_strdup(tmpl)) != NULL ? xxx = &tmp[len - 6] : 0;	
	while (fd < 0)
	{
		len = -1;
		fd = open("/dev/random", O_RDONLY);
		while (++len < 6)
		{
			read(fd, &buf, 1);
			xxx[len] = g_letters[(buf + 300) % 62];
		}
		close(fd);
		fd = open(tmp, O_RDWR | O_CREAT | O_EXCL | O_CLOEXEC, 0666);
	}
	unlink(tmp);
	free(tmp);
	return (fd);
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
