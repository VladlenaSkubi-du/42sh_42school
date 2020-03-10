/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 15:53:46 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/10 16:26:17 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

/*
** Readline_choice is a router to analyse what was pushed by the user
** @sy is symbol
*/

int		readline_choice(char sy)
{
	if (ctrl_key(sy) == OUT)
		return (OUT);
	if (sy == '\033')
	{
		check_menu();
		escape_init();
	}
	else if (ft_isprint(sy))
	{
		check_menu();
		char_add(sy, NULL);
		kirill_lgbt(sy);
	}
	return (0);
}

char	*readline(void)
{
	char			temp;

	init_termcap();
	while (read(1, &temp, 1) && temp != '\n')
	{
		if (readline_choice(temp) == OUT)
			break ;
	}
	if (g_rline.cmd_len > 0)
	{
		check_menu();
		position_cursor_for_menu(g_rline.cmd_len);
		putcap("cd");
	}
	else
		ft_putendl_fd(0, STDIN_FILENO);
	action_alloc_management(NULL, 1);
	save_current_grline(2);
	return (g_rline.cmd);
}

void	init_readline(void)
{
	if (ioctl(1, TIOCGWINSZ, &g_screen))
	{
		ft_putendl_fd("Can't get terminal dimensions", 2);
		clean_everything();
		exit(TERMINAL_EXISTS);
	}
	g_rline.prompt_len = prompt_len();
	g_rline.cmd = (char *)ft_xmalloc(CMD_SIZE + 1);
	g_rline.cmd_len = 0;
	g_rline.pos = 0;
	g_rline.pos_x = g_rline.prompt_len;
	if (g_rline.prompt_len >= g_screen.ws_col)
		g_rline.pos_x = g_rline.prompt_len % g_screen.ws_col;
	g_rline.pos_y = 0;
	g_rline.str_num = 1;
	g_rline.cmd_buff_len = CMD_SIZE + 1;
	g_rline.flag = 0;
}
