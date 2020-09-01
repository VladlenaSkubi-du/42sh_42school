/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 18:55:29 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/25 20:25:47 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"
#define ESC_NUM 12

/*
** @seq_base is an array of chars
** @seq_action is an array of functions
** Both arrays are of the same size @ESC_NUM
** @escape_check is a function that helps to
** match the arrays
*/

int		sequence_process(int sequence_num)
{
	int		(*seq_action[ESC_NUM])(void);

	seq_action[0] = arrow_right_jumpcharright;
	seq_action[1] = arrow_up_history;
	seq_action[2] = arrow_left_jumpcharleft;
	seq_action[3] = arrow_down_history;
	seq_action[4] = esc_r_clearline;
	seq_action[5] = delete_cutcharunder;
	seq_action[6] = esc_b_jumpwordleft;
	seq_action[7] = esc_f_jumpwordright;
	seq_action[8] = esc_d_cuttillwordend;
	seq_action[9] = esc_t_swapwords;
	seq_action[10] = ctrl_up_jumplineup;
	seq_action[11] = ctrl_down_jumplinedown;
	return ((*seq_action[sequence_num])());
}

int		escape_init(void)
{
	char	*seq_base[ESC_NUM];

	seq_base[0] = "[C";
	seq_base[1] = "[A";
	seq_base[2] = "[D";
	seq_base[3] = "[B";
	seq_base[4] = "r";
	seq_base[5] = "[3~";
	seq_base[6] = "b";
	seq_base[7] = "f";
	seq_base[8] = "d";
	seq_base[9] = "t";
	seq_base[10] = "[1;5A";
	seq_base[11] = "[1;5B";
	return (escape_check(seq_base));
}

/*
** When we push a button that has a more than a 1-char-sequence
** under it, the first read in the readline-function catches
** only the first char from the sequence. All the other are saved
** in a buffer and can be read after here. If the sequence
** is the same as saved in the array @seq_base - it will be
** directed to the right function ot perform the action
*/

int		escape_check(char **seq_base)
{
	int		i;
	char	buff[16];
	int		stage;

	i = 0;
	ft_bzero(buff, 16);
	while (read(STDIN_FILENO, buff + i, 1))
	{
		stage = 0;
		while (stage < ESC_NUM)
		{
			if (!ft_strncmp(buff, seq_base[stage], i + 1))
				break ;
			stage++;
		}
		if (stage == ESC_NUM)
			return (incorrect_sequence());
		if (!ft_strncmp(buff, seq_base[stage],
				ft_strlen(seq_base[stage]) + 1))
			return (sequence_process(stage));
		i++;
	}
	return (0);
}
