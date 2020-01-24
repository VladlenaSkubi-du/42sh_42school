/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 19:03:25 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/24 13:31:50 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"
#define CTRL_NUM 16

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
	ctrl_action[14] = make_ctrl_y_wrap;
	ctrl_action[15] = auto_completion;
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
	ctrl_base[14] = '\031';
	ctrl_base[15] = '\011';
	return (ctrl_process(ctrl_base, sy));
}
