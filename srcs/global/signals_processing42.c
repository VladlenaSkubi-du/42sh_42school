/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_processing42.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 16:45:15 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/21 17:53:19 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int					signals_reroute(int from)
{
	if (from == 1)
	{
		signal(SIGINT, signal_ctrl_c_readline);
		signal(SIGWINCH, signal_screen_readline);
		signal(SIGCONT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
	}
	else if (from == 2)
	{
		signal(SIGINT, signal_ctrl_c_parser);
		signal(SIGWINCH, SIG_DFL);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGCONT, SIG_IGN);
	}
	return (0);
}

void				signal_ctrl_c_readline(int sig)
{
	if (sig != SIGINT)
		return ;
	if (g_rline.flag & AFTER_LINE_HIST)
	{
		ft_putchar_fd('\033', STDIN_FILENO);
		// ft_putchar_fd('\n', STDOUT_FILENO);
		position_cursor("ch", 0, 0);
		tputs(g_cap.cd, 1, printc);
		g_rline.flag |= SIGNAL_C_QUESTION;
		return ;
	}
	else
	{
		check_after_line();
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	bzero_readline();
	g_prompt.prompt_func = main_prompt;
	g_prompt.prompt_func();
}

void				signal_screen_readline(int sig)
{
	if (sig != SIGWINCH)
		return ;
	check_after_line();
	position_cursor("ch", 0, 0);
	tputs(g_cap.cd, 1, printc);
	init_terminal_screen();
	g_rline.pos = 0;
	g_rline.pos_x = count_prompt_len();
	g_rline.pos_y = 0;
	g_rline.str_num = 1;
	g_prompt.prompt_func();
	if (g_rline.cmd_len >= g_screen.ws_col)
	{
		if (g_rline.cmd_len / g_screen.ws_col >
				g_screen.ws_row - 1)
			return ;
	}
	input_the_line_readline();
}

void				signal_ctrl_c_parser(int sig)
{
	if (sig != SIGINT)
		return ;
	ft_putendl_fd("\nstopped by signal SIGINT", STDOUT_FILENO);
}
