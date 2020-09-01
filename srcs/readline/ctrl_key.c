/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 18:54:06 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/25 20:34:33 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
** ctrl_action[7] is for ctrl_b
** ctrl_action[8] is for ctrl-f
** ctrl_action[9] is for ctrl-d
** ctrl_action[10] is for backspace key
** ctrl_action[11] is for ctrl-h
** ctrl_action[13] is for ctrl-shift-"-" or ctrl-_
*/

int			ctrl_call(int call_num)
{
	int		(*ctrl_action[CTRL_NUM])(void);

	ctrl_action[0] = ctrl_k_cuttillend;
	ctrl_action[1] = ctrl_l_clearscreen;
	ctrl_action[2] = ctrl_t_swapchars;
	ctrl_action[3] = ctrl_u_cuttillbeg;
	ctrl_action[4] = ctrl_w_cuttillwordbeg;
	ctrl_action[5] = ctrl_a_jumplinebeg;
	ctrl_action[6] = ctrl_e_jumplineend;
	ctrl_action[7] = arrow_left_jumpcharleft;
	ctrl_action[8] = arrow_right_jumpcharright;
	ctrl_action[9] = delete_cutcharunder;
	ctrl_action[10] = backspace_cutcharbefore;
	ctrl_action[11] = backspace_cutcharbefore;
	ctrl_action[12] = ctrl_x_ctrl_u_undo;
	ctrl_action[13] = undo_wrap;
	ctrl_action[14] = ctrl_p_paste;
	ctrl_action[15] = tab_completion;
	ctrl_action[16] = ctrl_r_history;
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
	int		i;

	i = 0;
	while (i < CTRL_NUM)
	{
		if (ctrl_base[i] == sy)
			return (ctrl_call(i));
		i++;
	}
	return (0);
}

int			ctrl_x_ctrl_u_undo(void)
{
	char			next;

	check_after_line();
	read(1, &next, 1);
	if (next == '\025')
		undo(1);
	else
		incorrect_sequence();
	return (0);
}

int			undo_wrap(void)
{
	return (undo(1));
}
