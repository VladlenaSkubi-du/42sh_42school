/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_readline42.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 19:01:07 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/25 19:01:08 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "shell42.h"

/*
** Buffer for the inserted cmd-line is of CMD_SIZE in the
** beginning and grows by the usage of shell - it is freed
** only after the session is over
*/

void			init_readline(void)
{
	g_rline.cmd = (char *)ft_xmalloc(CMD_SIZE + 1);
	g_rline.cmd_len = 0;
	g_rline.pos = 0;
	g_rline.pos_x = 0;
	g_rline.pos_y = 0;
	g_rline.str_num = 1;
	g_rline.cmd_buff_len = CMD_SIZE + 1;
	g_rline.flag = 0;
}

void			bzero_readline(void)
{
	init_terminal_screen();
	if (g_rline.cmd[0])
		ft_bzero(g_rline.cmd, g_rline.cmd_buff_len);
	g_rline.cmd_len = 0;
	g_rline.pos = 0;
	g_rline.pos_x = count_prompt_len();
	g_rline.pos_y = 0;
	g_rline.str_num = 1;
	if (!(g_rline.flag & PROMPTLEN_ZERO))
		g_rline.flag = 0;
}

void			realloc_readline_cmd(void)
{
	g_rline.cmd = (char *)ft_realloc(g_rline.cmd,
		g_rline.cmd_len, g_rline.cmd_buff_len,
		g_rline.cmd_buff_len + CMD_SIZE);
	g_rline.cmd_buff_len += CMD_SIZE;
}

/*
** If we did not get describtion of the terminal
** or there is no termcap library, we are still able
** to make the line alterable with readline-simple
** And from here we go to parser in the interactive mode
*/

int				start_readline42(int tmp)
{
	char		*final;

	bzero_readline();
	(tmp != 1) ? readline_simple() : readline();
	reset_canonical_input();
	signals_reroute(2);
	final = finalize_cmd(g_rline.cmd);
	free(g_hist.hist[g_hist.last + 1]);
	parser(final);
	return (0);
}

/*
** By going to parser, we cut the line: all the spaces
** and "\n" and "\t" and the buffer that was used in
** the g_rline structure - to have only the cmd_line
*/

char			*finalize_cmd(char *cmd)
{
	char		*out;
	char		*tmp;

	tmp = ft_strtrim(cmd);
	if (ft_strlen(tmp) == 0)
	{
		out = ft_xmalloc(1);
		free(tmp);
		return (out);
	}
	else
		out = ft_strjoin(cmd, "\n");
	free(tmp);
	return (out);
}
