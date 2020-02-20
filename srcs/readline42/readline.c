/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 15:53:46 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/20 20:30:27 by sschmele         ###   ########.fr       */
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
		char_add(sy);
	}
	return (0);
}

char	*readline(void)
{
	char			temp;

	init_termcap();
	while (read(1, &temp, 1) && temp != '\n')
	{
		if (ioctl(1, TIOCGWINSZ, &g_screen))
		{
			ft_putendl_fd("Can't get terminal dimensions", 2); //TODO delete
			return (NULL);
		}
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
	return (g_rline.cmd);
}

void	init_readline(void)
{
	if (g_prompt.prompt_func == main_prompt)
		g_rline.prompt_len = ft_strlen("e-bash> ");
	else if (g_prompt.prompt_func == dquote_prompt)
		g_rline.prompt_len = ft_strlen("dquote> ");
	else if (g_prompt.prompt_func == heredoc_prompt)
		g_rline.prompt_len = ft_strlen("heredoc> ");
	else if (g_prompt.prompt_func == other_prompt)
		g_rline.prompt_len = ft_strlen("> ");
	else if (g_prompt.prompt_func == pipe_prompt)
		g_rline.prompt_len = ft_strlen("pipe> ");
	else if (g_prompt.prompt_func == subshell_prompt)
		g_rline.prompt_len = ft_strlen("subshell> ");
	else if (g_prompt.prompt_func == cursh_prompt)
		g_rline.prompt_len = ft_strlen("cursh> ");
	else if (g_prompt.prompt_func == cmdandor_prompt)
		g_rline.prompt_len = ft_strlen("cmdandor> ");
	g_rline.cmd = (char *)ft_xmalloc(CMD_SIZE + 1);
	g_rline.cmd_len = 0;
	g_rline.pos = 0;
	g_rline.pos_x = g_rline.prompt_len;
	g_rline.pos_y = 0;
	g_rline.str_num = 1;
	g_rline.cmd_buff_len = CMD_SIZE + 1;
	g_rline.flag = 0;
}
