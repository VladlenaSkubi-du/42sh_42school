/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 16:43:04 by vladlenasku       #+#    #+#             */
/*   Updated: 2020/01/02 19:49:36 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#define			OUT_BUF 10

typedef struct			s_buf
{
	char				**buff;
	int					buff_lines;
	size_t				i;
	int					size;
	int					t_width;
	int					s_width;
}						t_buf;

static char			**buffer_col_init(int *buf_width, int *buf_lines, int word_len, int word_nb)
{
	char			**buffer;
	size_t			i;

	*buf_width = (g_screen.ws_col / word_len) * word_len + 1;
	*buf_lines = g_screen.ws_col / word_len;
	*buf_lines = word_nb / *buf_lines + (word_nb % *buf_lines ? 1 : 0);
	buffer = (char**)ft_xmalloc(sizeof(char*) * (*buf_lines + 1));
	buffer[*buf_lines] = 0;
	i = -1;
	while (++i < *buf_lines)
		buffer[i] = (char*)ft_xmalloc(*buf_width + 1);
	return (buffer);
}

int					buffer_col_print(char *add, int word_len, int word_nb)
{
	static char		**buffer;
	static int		buf_lines;
	static int		buf_width;
	static size_t	i;

	if (!buffer)
		buffer = buffer_col_init(&buf_width, &buf_lines, word_len, word_nb);
	ft_memcpy(buffer[i % buf_lines] + (i / buf_lines * buf_width), add, ft_strlen(add));
	ft_straddsy(buffer[i % buf_lines] + (i / buf_lines * buf_width), '\t');
	if (i++ == word_nb - 1)
	{
		ft_arrdel(buffer);
		buffer = NULL;	
	}
	// ft_strcpy(buffer[i][j], add);
	// buffer[i] = ft_straddsy(buffer[i][j + ft_strlen(add)], '\t');
	return (0);
}