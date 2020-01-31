/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_processing42.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:43:36 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/31 19:29:54 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

//TODO сделать нормальные защищенные сигналы

/*
** @from = 2 from the main
**		= 3 if out
*/

int				signal_ctrl_c(void)
{
	if (g_prompt.prompt_func != main_prompt)
		g_prompt.prompt_func = main_prompt;
	free(g_rline.cmd);
	g_rline.cmd = NULL;
	g_rline.cmd_len = 0;
	return (OUT);
}

int				ctrl_d_with_other_prompt(void)
{
	g_cmd = (char*)ft_xmalloc(g_dquote.buf_len - 2 + 1);
	g_dquote.flag_esc = 0;
	g_cmd = copy_without_slash_enter(g_cmd, g_dquote.cmd_buf, &g_cmd_size, 2);
	if (!g_cmd || g_cmd[0] == 0)
	{
		free(g_cmd);
		btin_exit(SUCCESS);
	}
	free(g_dquote.cmd_buf);
	g_dquote.cmd_buf = NULL;
	return (1);
}

int				ctrl_d_with_dquote_prompt(void)
{
	int			tmp;
	
	g_dquote.flag_quote = 0;
	if (g_dquote.flag_esc > 0)
	{
		g_cmd = (char*)ft_xmalloc(g_dquote.buf_len -
			(1 * (g_dquote.flag_esc)) + g_cmd_size + 1);
		g_dquote.flag_esc = 0;
		g_cmd = copy_without_slash_enter(g_cmd, g_dquote.cmd_buf,
			&g_cmd_size, 1);
		free(g_dquote.cmd_buf);
	}
	else
		g_cmd = g_dquote.cmd_buf;
	g_prompt.prompt_func = main_prompt;
	//history
	tmp = ft_last_stack(&g_dquote.check);
	error_handler(SYNTAX_ERROR | (ERR_SQUOTE << 8),
		(tmp == 5) ? "\"" : "\'");
	return (2);
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

void			sig_fork(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd(0, STDIN_FILENO);
		return ; //TODO чистим parser
	}
}
