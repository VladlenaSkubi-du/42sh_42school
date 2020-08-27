/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_simple.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 18:50:33 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/27 22:04:40 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int					bell_sound(void)
{
	write(STDOUT_FILENO, "\a", 1);
	return (1);
}

int					sreadline_choice(char sy)
{
	if (sy == '\033')
		sescape_init();
	else if (ft_isprint(sy))
	{
		if (schar_add(sy) == OUT)
			return (OUT);
	}
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
	else if (sy == '\004')
		make_sexit();
	return (0);
}

int					readline_simple(void)
{
	char			c;

	while (read(STDIN_FILENO, &c, 1) && c != '\n')
	{
		if (sreadline_choice(c) == OUT)
			break ;
	}
	ft_putendl_fd(0, STDOUT_FILENO);
	return (0);
}

int					make_sexit(void)
{
	t_process		*pos;

	if (g_rline.pos == 0 && g_rline.cmd_len == 0 &&
			g_prompt.prompt_func == main_prompt)
	{
		pos = (t_process*)ft_xmalloc(sizeof(t_process));
		pos->argv = (char**)ft_xmalloc(3 * sizeof(char*));
		pos->argv[0] = ft_strdup("exit");
		pos->argv[1] = ft_strdup("0");
		reset_canonical_input();
		if (btin_exit(pos) == BTIN_ERROR)
		{
			free_t_process(pos);
			return (OUT);
		}
	}
	else if (g_rline.pos == 0 && g_rline.cmd_len == 0 &&
			g_prompt.prompt_func != main_prompt)
	{
		if (g_rline.cmd_len >= g_rline.cmd_buff_len - 1)
			realloc_readline_cmd();
		g_rline.cmd = ft_straddsy(g_rline.cmd, EOF);
		return (OUT);
	}
	return (0);
}
