/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 19:03:25 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/14 19:44:28 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

/*
** Ctrl: Ctrl-k, ctrl-t, ctrl-u (ctrl-w) is here (I take)
*/

int			make_ctrl_x(void)
{
	char	next;

	read(1, &next, 1);
	if (next == '\025')
		undo(1);
	else
		incorrect_sequence();
	return (0);
}

int			ctrl_key(char sy)
{
	if (sy == '\013')
		make_ctrl_k();
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
	return (0);
}
