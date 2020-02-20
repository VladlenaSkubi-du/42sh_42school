/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   question_if_many_compl.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 14:59:21 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/20 20:13:08 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int					ask_output(size_t total, int buf_lines,
						size_t pos_back, int len_x)
{
	// char			c;
	// int				len;
	// int				total_len;
	// int				lines_len;
	// char			*question;

	// count_comment_len(&total_len, &lines_len, total, buf_lines);
	// len = 20 + 16 + 18 + total_len + lines_len;
	// insert_word_by_letters(NULL, 0);
	// insert_word_by_letters("e-bash: display all ", 0);
	// question = ft_itoa(total);
	// insert_word_by_letters(question, 0);
	// insert_word_by_letters(" possibilities (", 0);
	// free(question);
	// question = ft_itoa(buf_lines);
	// insert_word_by_letters(question, 0);
	// insert_word_by_letters(" lines)? [y or n] ", 0);
	// free(question);
	// read(STDOUT_FILENO, &c, 1);
	// if (c == 'y' || c == 'Y')
	// 	return (clean_output_question(1, pos_back, len, len_x));
	// clean_output_question(0, pos_back, len, len_x);
	return (1);
}

/*
** Here we count how long are the values of @total and @buf_len
** to get the full length of the question string and be able
** to clean it after
*/

int					count_comment_len(int *total_len,
						int *lines_len, size_t total,
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
						int len, int len_x)
{
	int				lines_nb;

	lines_nb = len / g_screen.ws_col + ((from == 0) ? 1 : 0);
	if ((len + 1) % g_screen.ws_col == 0)
		lines_nb += 1;
	if (lines_nb > 1)
		position_cursor("UP", 0, lines_nb - 1);
	position_cursor("ch", 0, 0);
	tputs(g_cap.cd, 1, printc);
	if (from == 0)
	{
		position_cursor("ch", 0, len_x);
		tputs(g_cap.up, 1, printc);
		g_rline.pos = pos_back;
		move_cursor_from_old_position(g_rline.cmd_len, 'l');
		return (0);
	}
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
