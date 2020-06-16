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

	seq_action[0] = key_right_proc; //rename: arrow_right_jumpcharright
	seq_action[1] = key_up_proc; //rename: arrow_up_history
	seq_action[2] = key_left_proc; //rename: arrow_left_jumpcharleft
	seq_action[3] = key_down_proc; //rename: arrow_down_history
	seq_action[4] = esc_r; //rename: esc_r_clearline
	seq_action[5] = delete_process; //rename: delete_cutcharunder
	seq_action[6] = word_left_proc; //rename: esc_b_jumpwordleft
	seq_action[7] = word_right_proc; //rename: esc_f_jumpwordright
	seq_action[8] = esc_d; //rename: esc_d_cuttillwordend
	seq_action[9] = esc_t; //rename: esc_d_swapwords
	seq_action[10] = jump_up; //rename: ctrl_up_jumplineup
	seq_action[11] = jump_down; //rename: ctrl_down_jumplinedown
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
	while (read(1, buff + i, 1))
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
