/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42signals_processing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:43:36 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/16 19:33:27 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

//TODO сделать нормальные защищенные сигналы

/*
** @from = 1 if from readline
** 		= 2 from the main
**		= 3 if out
*/

int             signals_reroute(int from)
{
	if (from == 1)
	{
		signal(SIGTSTP, sig_readline);
		signal(SIGINT, sig_readline);
		signal(SIGTERM, SIG_IGN);
		signal(SIGCONT, sig_readline);
	}
	else if (from == 2)
	{
		signal(SIGINT, sig_fork);
	}
	else
	{
		signal(SIGTSTP, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		signal(SIGTERM, SIG_DFL);
		signal(SIGCONT, SIG_DFL);
	}
	return(0);
}

void            sig_readline(int sig)
{
	if (sig == SIGTSTP)
		make_ctrl_y(1, NULL);
	else if (sig == SIGINT)
	{
		clean_readline42();
	}
	else if (sig == SIGCONT)
	{
		printf("Hi\n");
	}
}

void            sig_fork(int sig)
{
	if (sig == SIGINT)
	{
		//TODO чистим parser
	}
}