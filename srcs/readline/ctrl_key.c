#include "shell42.h"
#include "readline.h"
#define CTRL_NUM 17

/*
** @ctrl_base is an array of chars
** @ctrl_action is an array of functions
** Both arrays are of the same size @CTRL_NUM
** @ctrl_process is a function that helps to
** match the arrays
*/

/*
** ctrl_action[9] is for ctrl-d
** ctrl_action[10] is for backspace key
** ctrl_action[11] is for ctrl-h
** ctrl_action[13] is for ctrl-shift-"-" or ctrl-_
*/

int			ctrl_call(size_t call_num)
{
	int		(*ctrl_action[CTRL_NUM])(void);

	ctrl_action[0] = make_ctrl_k; //rename: ctrl_k_cuttillend
	ctrl_action[1] = make_ctrl_l; //rename: ctrl_l_clearscreen
	ctrl_action[2] = make_ctrl_t; //rename: ctrl_t_swapchars
	ctrl_action[3] = make_ctrl_u; //rename: ctrl_u_cuttillbeg
	ctrl_action[4] = make_ctrl_w; //rename: ctrl_w_cuttillwordbeg
	ctrl_action[5] = make_ctrl_a; //rename: ctrl_a_jumplinebeg
	ctrl_action[6] = make_ctrl_e; //rename: ctrl_e_jumplineend
	ctrl_action[7] = key_left_proc; //rename: ctrl_b_jumpcharleft
	ctrl_action[8] = key_right_proc; //rename: ctrl_f_jumpcharright
	ctrl_action[9] = delete_process; //rename: delete_cutcharunder
	ctrl_action[10] = backspace_process; //rename: backspace_cutcharbefore
	ctrl_action[11] = backspace_process; //rename: backspace_cutcharbefore
	ctrl_action[12] = make_ctrl_x; //rename: ctrl_x_ctrl_u_undo
	ctrl_action[13] = undo_wrap;
	ctrl_action[14] = make_ctrl_p_wrap; //rename: ctrl_p_paste
	ctrl_action[15] = auto_completion; //rename: tab_completion
	ctrl_action[16] = make_ctrl_r_history; //rename: ctrl_r_history
	return ((*ctrl_action[call_num])());
}

int			ctrl_key(char sy)
{
	char	ctrl_base[CTRL_NUM];

	ctrl_base[0] = '\013';
	ctrl_base[1] = '\014';
	ctrl_base[2] = '\024';
	ctrl_base[3] = '\025';
	ctrl_base[4] = '\027';
	ctrl_base[5] = '\001';
	ctrl_base[6] = '\005';
	ctrl_base[7] = '\002';
	ctrl_base[8] = '\006';
	ctrl_base[9] = '\004';
	ctrl_base[10] = 127;
	ctrl_base[11] = '\010';
	ctrl_base[12] = '\030';
	ctrl_base[13] = '\037';
	ctrl_base[14] = '\020';
	ctrl_base[15] = '\011';
	ctrl_base[16] = '\022';
	return (ctrl_process(ctrl_base, sy));
}

int			ctrl_process(char *ctrl_base, char sy)
{
	size_t	i;

	i = 0;
	while (i < CTRL_NUM)
	{
		if (ctrl_base[i] == sy)
			return (ctrl_call(i));
		i++;
	}
	return (0);
}
