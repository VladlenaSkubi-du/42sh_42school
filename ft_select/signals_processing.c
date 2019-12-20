/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_processing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:29:48 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/20 12:58:31 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** key == 3 - SIGINT
** key == 4 - SIGTERM
** key == 28 - SIGQUIT(Ctrl-\)
** key == 26 - SIGTSTP (ctrl-Z)
** resize - SIGWINCH
*/

void				redirect_signals(void)
{
	signal(SIGWINCH, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGTSTP, signal_handler);
	signal(SIGCONT, signal_handler);
	signal(SIGQUIT, signal_handler);
}

void				signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		save_for_exit(NULL, 0);
		exit(130);
	}
	if (sig == SIGTSTP)
		save_for_exit(NULL, 2);
	if (sig == SIGWINCH)
		resize_monitor(NULL, 0, 0, 0);
	if (sig == SIGCONT)
		save_for_exit(NULL, 3);
	if (sig == SIGQUIT)
	{
		save_for_exit(NULL, 4);
		exit(131);
	}
}
