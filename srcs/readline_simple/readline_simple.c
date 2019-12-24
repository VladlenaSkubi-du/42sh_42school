/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_simple.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 15:49:40 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/24 17:05:27 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int					bell_sound(void)
{
	write(STDOUT_FILENO, "\a", 1);
	return (1);
}

int					sescape_init(void)
{
	char			*seq_base[SESC_NUM];

	seq_base[0] = "[C";
	seq_base[1] = "[A";
	seq_base[2] = "[D";
	seq_base[3] = "[B";
	seq_base[4] = "r";
	return (sescape_check(seq_base));
}

int					sreadline_choice(char sy)
{
	if (sy == '\033')
		sescape_init();
	else if (ft_isprint(sy))
		schar_add(sy);
	else if (sy == 127 || sy == '\010')
		sbackspace_proc();
	else if (sy == '\002')
		sesc_left();
	else if (sy == '\006')
		sesc_right();
	else if (sy == '\001')
		make_sctrl_a();
	else if (sy == '\005')
		make_sctrl_e();
	else if (sy == '\013')
		make_sctrl_k();
	else if (sy == '\025')
		make_sctrl_u();
	return (0);
}

char				*readline_simple(void)
{
	char			c;

	init_readline();
	if (set_noncanonical_input() == -1)
	{
		ft_putendl_fd("Terminal can't be changed", 2);
		ft_putendl_fd("Use non-interactive shell", 2);
		return (NULL);
	}
	main_promt(); //сделать условие
	while (read(STDIN_FILENO, &c, 1) && c != '\n')
	{
		if (ioctl(1, TIOCGWINSZ, &g_screen))
		{
			ft_putendl_fd("Can't get terminal dimensions", 2);
			return (NULL);
		}
		sreadline_choice(c);
	}
	if (reset_canonical_input())
		exit(1);
	return (g_rline.cmd);
}
