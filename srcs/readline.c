/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 15:53:46 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/18 12:47:37 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

/*
** Readline_choice is a router to analyse what was pushed by the user
** @sy is symbol
*/

int		readline_choice(char sy)
{
	ctrl_key(sy); // Check if it is possible to add this to escape_process
	if (sy == '\033')
		escape_init();
	else if (ft_isprint(sy))
	{
		if (char_add(sy))
			return (-1);
	}
	return (0);
}

char	*readline(void)
{
	char			temp;
	
	init_readline();
	if (set_noncanonical_input() == -1)
	{
		ft_putendl_fd("Terminal can't be changed", 2); //исправить
		return (NULL);
	}
	if (main_promt())
		return (NULL);
	while (read(1, &temp, 1) && temp != '\n')
	{
		ioctl(1, TIOCGWINSZ, &g_screen);
		if (readline_choice(temp) < 0)
			return (NULL);
	}
	reset_canonical_input(); // Add error
	action_alloc_management(0, 1);
	return (g_rline.cmd);
}

void	init_readline(void)
{
	g_rline.cmd = (char *)ft_xmalloc(CMD_SIZE + 1);
	g_rline.pos = 0;
	g_rline.str_num = 0;
	g_rline.cmd_buff_len = CMD_SIZE;
	g_rline.flag = 0;
}
