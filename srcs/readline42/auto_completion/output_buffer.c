/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 16:43:04 by vladlenasku       #+#    #+#             */
/*   Updated: 2020/01/04 17:00:59 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#define				OUT_BUF 10

void				buf_add(char *str, size_t size)
{
	static char		buf[OUT_BUF];
	static char		*ptr = buf;

	if (!str && !size)
	{
		write(1, buf, ptr - buf);
		ptr = buf;
	}
	else if (size + (size_t)(ptr - buf) < OUT_BUF)
	{
		ft_memcpy(ptr, str, size);
		ptr += size;
	}
	else
	{
		write(1, buf, ptr - buf);
		write(1, str, size);
		ptr = buf;
	}
}

int					buffer_col_print(char *add, t_completion *menu_buf)
{
	if (!menu_buf->buffer)
		buffer_col_calc(menu_buf);
	ft_memcpy(menu_buf->buffer[menu_buf->i % menu_buf->buf_lines]
		+ (menu_buf->i / menu_buf->buf_lines * menu_buf->word_len),
			add, ft_strlen(add));
	ft_straddsy(menu_buf->buffer[menu_buf->i % menu_buf->buf_lines]
		+ (menu_buf->i / menu_buf->buf_lines * menu_buf->word_len), '\t');
	if (menu_buf->i++ == menu_buf->word_nb - 1)
		buffer_col_finish_and_del(menu_buf);
	return (0);
}

void				buffer_col_calc(t_completion *menu_buf)
{
	size_t			i;

	menu_buf->buf_width = (g_screen.ws_col / menu_buf->word_len) * menu_buf->word_len + 1;
	menu_buf->buf_lines = g_screen.ws_col / menu_buf->word_len;
	menu_buf->buf_lines = menu_buf->word_nb / menu_buf->buf_lines
		+ (menu_buf->word_nb % menu_buf->buf_lines ? 1 : 0);
	menu_buf->buffer = (char**)ft_xmalloc(sizeof(char*) * (menu_buf->buf_lines + 1));
	menu_buf->buffer[menu_buf->buf_lines] = 0;
	i = -1;
	while (++i < menu_buf->buf_lines)
		menu_buf->buffer[i] = (char*)ft_xmalloc(menu_buf->buf_width + 1);
}

void				buffer_col_finish_and_del(t_completion *menu_buf)
{
	size_t			i;

	i = -1;
	while (++i < menu_buf->buf_lines)
	{
		buf_add(menu_buf->buffer[i], menu_buf->buf_width);
		buf_add("\n", 1);
		free(menu_buf->buffer[i]);
	}
	free(menu_buf->buffer);
	menu_buf->buffer = NULL;
}

void				menu_buf_init(t_completion *menu_buf)
{
	menu_buf->buffer = NULL;
	menu_buf->buf_lines = 0;
	menu_buf->buf_width = 0;
	menu_buf->word_len = 0;
	menu_buf->word_nb = 0;
	menu_buf->i = 0;
}