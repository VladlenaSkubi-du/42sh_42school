/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 15:53:46 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/04 15:07:34 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

/*
** Readline_choice is a router to analyse what was pushed by the user
** @sy is symbol
*/

int		readline_choice(char sy)
{
	ctrl_key(sy);
	if (sy == '\033')
	{
		check_menu();
		escape_init();
	}
	else if (ft_isprint(sy))
	{
		check_menu();
		char_add(sy);
	}
	return (0);
}

char	*readline(void)
{
	char			temp;
	size_t			len;

	init_readline();
	if (set_noncanonical_input() == -1)
	{
		ft_putendl_fd("Terminal can't be changed", 2);
		ft_putendl_fd("Use non-interactive shell", 2);
		return (NULL);
	}
	main_promt(); //сделать условие
	while (read(1, &temp, 1) && temp != '\n')
	{
		if (ioctl(1, TIOCGWINSZ, &g_screen))
		{
			ft_putendl_fd("Can't get terminal dimensions", 2);
			return (NULL);
		}
		readline_choice(temp);
	}
	len = ft_strlen(g_rline.cmd);
	if (len > 0)
	{
		position_cursor_for_menu(len);
		putcap("cd");
	}
	if (reset_canonical_input())
		exit(1);
	action_alloc_management(0, 1);
	return (g_rline.cmd);
}

void	init_readline(void)
{
	g_rline.cmd = (char *)ft_xmalloc(CMD_SIZE + 1);
	g_rline.pos = 0;
	g_rline.str_num = 0;
	g_rline.cmd_buff_len = CMD_SIZE + 1;
	g_rline.flag = 0;
}
