/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_processing42.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:43:36 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/18 19:47:36 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

//TODO сделать нормальные защищенные сигналы

/*
** @from = 2 from the main
**		= 3 if out
*/

int					signal_ctrl_c(void)
{
	size_t			pos_old;
	
	if (g_rline.cmd_len > 0)
	{
		check_menu();
		pos_old = g_rline.pos;
		if (!(g_rline.pos == 0 &&
			g_rline.cmd_len == 0))
		{
			g_rline.pos = g_rline.cmd_len;
			move_cursor_from_old_position(pos_old, 'r');
		}
		putcap("cd");
	}
	if (g_prompt.prompt_func != main_prompt)
		g_prompt.prompt_func = main_prompt;
	free(g_rline.cmd);
	g_rline.cmd = NULL;
	g_rline.cmd_len = 0;
	return (OUT);
}

int					signal_ctrl_d(void)
{
	char			*swap;
	size_t			len_swap;

	check_menu();
	if (g_rline.pos == 0 && g_rline.cmd_len == 0)
		if (route_exit() == OUT)
			return (OUT);
	if (g_rline.pos < g_rline.cmd_len)
	{
		undo(0);
		swap = g_rline.cmd + g_rline.pos + 1;
		len_swap = ft_strlen(swap);
		ft_strcpy(g_rline.cmd + g_rline.pos, swap);
		ft_bzero(g_rline.cmd + g_rline.pos + len_swap,
			g_rline.cmd_buff_len - g_rline.cmd_len);
		putcap("cd");
		ft_putstr_fd(g_rline.cmd + g_rline.pos, 1);
		recount_str_num(g_rline.cmd_len - 1);
		g_rline.cmd_len--;
		move_cursor_back_after_print(1);
	}
	else
		return (incorrect_sequence());
	return (0);
}

int					route_exit(void)
{
	if (g_prompt.prompt_func == main_prompt)
	{
		action_alloc_management(NULL, 1);
		reset_canonical_input();
		clean_readline42();
		btin_exit(SUCCESS);
	}
	if (g_prompt.prompt_func != main_prompt)
	{
		g_rline.cmd = ft_straddsy(g_rline.cmd, EOF);
		return (OUT);
	}
	return (0);
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

void			sig_screen(int sig)
{
	// size_t		i;
	
	// i = 0;
	// check_menu();
	ioctl(1, TIOCGWINSZ, &g_screen);
	// while (g_rline.pos)
	// 	key_left_proc();
	// position_cursor("ch", 0, 0);
	// putcap("cd");
	// g_prompt.prompt_func();
	// while (i < g_rline.cmd_len)
	// {
	// 	insert_char(g_rline.cmd[i]);
	// 	i++;
	// }
}

void			sig_fork(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd(0, STDIN_FILENO);
		return ; //TODO чистим parser
	}
}
