/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_processing42.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:43:36 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/03 17:04:48 by sschmele         ###   ########.fr       */
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
		tputs(g_cap.cd, 1, printc);
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
		g_rline.cmd_len--;
		front_set_cursor_jmp(&g_rline.pos, &g_rline.pos_x,
			&g_rline.pos_y, 1);
		tputs(g_cap.cd, 1, printc);
		front_insert_cmd_till_the_end(g_rline.pos_y + 1);
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
	printf("hello\n");
	// check_menu();
	// front_set_cursor_jmp(&g_rline.pos, &g_rline.pos_x, &g_rline.pos_y, 1);
	// move_cursor_from_old_position(0, 'l');
	// position_cursor("ch", 0, 0);
	// tputs(g_cap.cd, 1, printc);
	// ioctl(1, TIOCGWINSZ, &g_screen);
	// g_prompt.prompt_func();
	// if (g_rline.prompt_len >= g_screen.ws_col)
	// 	g_rline.pos_x = g_rline.prompt_len % g_screen.ws_col;
	// front_insert_cmd_till_the_end(g_rline.pos_y + 1);
}

void			sig_fork(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd(0, STDIN_FILENO);
		return ; //TODO чистим parser
	}
}
