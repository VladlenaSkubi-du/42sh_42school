/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   question_if_many.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 14:59:21 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/24 13:31:50 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int					ask_output(size_t total, int buf_lines,
						size_t pos_back, unsigned short len_x)
{
	char			c;
	unsigned short	len;
	unsigned short	total_len;
	unsigned short	lines_len;

	count_comment_len(&total_len, &lines_len, total, buf_lines);
	len = 29 + 16 + 10 + total_len + lines_len;
	ft_printf("42sh: display all %u possibilities (%u lines)? [y or n] ",
		total, buf_lines);
	read(STDOUT_FILENO, &c, 1);
	if (c == 'y' || c == 'Y')
	{
		clean_output_question(1, pos_back, len, len_x);
		return (0);
	}
	clean_output_question(0, pos_back, len, len_x);
	return (1);
}

int					count_comment_len(unsigned short *total_len,
						unsigned short *lines_len, size_t total,
						int buf_lines)
{
	int				number;

	*total_len = (total == 0) ? 1 : 0;
	number = total;
	while (number != 0)
	{
		(*total_len)++;
		number /= 10;
	}
	*lines_len = (buf_lines == 0) ? 1 : 0;
	number = buf_lines;
	while (number != 0)
	{
		(*lines_len)++;
		number /= 10;
	}
	return (0);
}

int					clean_output_question(int from, size_t pos_back,
						unsigned short len, unsigned short len_x)
{
	unsigned short	lines_nb;

	if (len > g_screen.ws_col)
	{
		lines_nb = len / g_screen.ws_col + ((from == 0) ? 1 : 0);
		position_cursor("UP", 0, lines_nb);
	}
	if (from == 0)
	{
		position_cursor("ch", 0, len_x);
		if (len <= g_screen.ws_col)
			putcap("up");
		putcap("cd");
		g_rline.pos = pos_back;
		move_cursor_from_old_position(g_rline.cmd_len, 'l');
		return (0);
	}
	position_cursor("ch", 0, 0);
	putcap("cd");
	return (0);
}

int					clean_strings_compl(char *compl,
						char *tech_line, int flag)
{
	free(compl);
	free(tech_line);
	if (flag == 1)
		return (incorrect_sequence());
	return (0);
}
