/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_processing42.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:43:36 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/30 15:23:09 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

//TODO сделать нормальные защищенные сигналы

/*
** @from = 2 from the main
**		= 3 if out
*/

int				signal_ctrl_c(void)
{
	if (g_prompt.prompt_func != main_prompt)
		g_prompt.prompt_func = main_prompt;
	free(g_rline.cmd);
	g_rline.cmd = NULL;
	g_rline.cmd_len = 0;
	return (OUT);
}

int				signals_reroute(int from)
{
	if (from == 2)
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
	return (0);
}

void			sig_fork(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd(0, STDIN_FILENO);
		return ; //TODO чистим parser
	}
}
