/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   question_if_many_compl.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 14:59:21 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/17 17:13:30 by vladlenasku      ###   ########.fr       */
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

/*
** Here we count how long are the values of @total and @buf_len
** to get the full length of the question string and be able
** to clean it after
*/

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

/*
** If the answer is yes and all the options do not fit in the
** terminal screen, we clear
** the question and after, print all the options, a new prompt and
** the cmd-line if it was filled (return 0 to print_menu and do there)
** If the answer is other than y or Y, we just clear the question
** and return back to the state as the cmd-line had before TAB was
** pushed
*/

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

/*
** If there are no options for completion, we clear the 
** allocated @g_complete and @g_techline strings and ring
** the bell
*/

int					clean_strings_compl(char *compl,
						char *tech_line, int flag)
{
	free(compl);
	free(tech_line);
	if (flag == 1)
		return (incorrect_sequence());
	return (0);
}
