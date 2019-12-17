/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 19:03:25 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/17 15:42:46 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#define CTRL_NUM 14

int			ctrl_call(size_t call_num)
{
	int		(*ctrl_action[CTRL_NUM])(void);

	ctrl_action[0] = make_ctrl_k;
	ctrl_action[1] = make_ctrl_l;
	ctrl_action[2] = make_ctrl_t;
	ctrl_action[3] = make_ctrl_u;
	ctrl_action[4] = make_ctrl_w;
	ctrl_action[5] = make_ctrl_a;
	ctrl_action[6] = make_ctrl_e;
	ctrl_action[7] = key_left_proc;
	ctrl_action[8] = key_right_proc;
	ctrl_action[9] = delete_process;
	ctrl_action[10] = backspace_process;
	ctrl_action[11] = backspace_process;
	ctrl_action[12] = make_ctrl_x;
	ctrl_action[13] = undo_wrap;
	return ((*ctrl_action[call_num])());
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
	return (ctrl_process(ctrl_base, sy));
}

/*
int			ctrl_key(char sy)
{

	if (sy == '\013')
		make_ctrl_k();
	else if (sy == '\014')
		make_ctrl_l();
	else if (sy == '\024')
		make_ctrl_t();
	else if (sy == '\025')
		make_ctrl_u();
	else if (sy == '\027')
		make_ctrl_w();
	else if (sy == '\001')
		make_ctrl_a();
	else if (sy == '\005')
		make_ctrl_e();
	else if (sy == '\002')
		key_left_proc();
	else if (sy == '\006')
		key_right_proc();
	else if (sy == '\004')
		delete_process();
	else if (sy == 127 || sy == '\010')
		backspace_process();
	else if (sy == '\030')
		make_ctrl_x();
	else if (sy == '\037')
		undo(1);
	else if (sy == '\037')
		undo(1);
	return (0);
}
*/