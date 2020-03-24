/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 17:34:28 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/23 17:54:02 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

int					btin_fc_route_execution(t_btin_fc *fc_arg, int flags)
{
	char			*cmd;
	int				i;
	//проверка на пустой буфер истории

	printf("HISTORY\n");
	btin_history();
	
	if (flags & FLAG_E)
	{
		printf("editor = %s\n", fc_arg->editor);
		if (fc_arg->flag & ARG_FIRST)
			printf("first_buf = %d, cmd = %s\n", fc_arg->first_buf, g_hist.hist[fc_arg->first_buf]);
		if (fc_arg->flag & ARG_SECOND)
			printf("last_buf = %d, cmd = %s\n", fc_arg->last_buf, g_hist.hist[fc_arg->last_buf]);
		if (flags & FLAG_R)
			printf("reverse\n");
	}
	else if (flags & FLAG_L)
	{
		if (fc_arg->flag & ARG_FIRST)
			printf("first_buf = %d, first number = %d, cmd = %s\n", fc_arg->first_buf, fc_arg->first, g_hist.hist[fc_arg->first_buf]);
		if (fc_arg->flag & ARG_SECOND)
			printf("last_buf = %d, last number = %d, cmd = %s\n", fc_arg->last_buf, fc_arg->last, g_hist.hist[fc_arg->last_buf]);
		if (flags & FLAG_R)
			printf("reverse\n");
		if (flags & FLAG_N)
			printf("without numbers\n");
		else
			printf("with numbers\n");
	}
	else if (flags & FLAG_S)
	{
		if (fc_arg->s_cmd)
		{
			i = find_in_history(fc_arg->s_cmd);
			if (i == -1)
			{
				error_handler(VARIABLE_ERROR | (ERR_HISTORY_EXEC << 9), "fc");
				return (HIST_ERROR);
			}
			cmd = g_hist.hist[i];
			printf("to find: %s - command found: %s\n", fc_arg->s_cmd, g_hist.hist[i]);
		}
		if (fc_arg->flag & ARG_FIRST)
		{
			cmd = g_hist.hist[fc_arg->first_buf];
			printf("command number = %d, cmd = %s\n", fc_arg->first_buf, g_hist.hist[fc_arg->first_buf]);
		}
		if (fc_arg->s_comp)
		{
			cmd = make_history_assignments(fc_arg, cmd);
			printf("command to launch: %s\n", cmd);
			free(cmd);
		}
	}
	return (0);
}

char				*make_history_assignments(t_btin_fc *fc_arg, char *cmd)
{
	int				i;
	int				buf_len;
	char			*buf;
	int				eq;
	char			*what;
	
	buf_len = CMD_SIZE;
	buf = (char*)ft_xmalloc(buf_len + 1);
	ft_strcpy(buf, cmd);
	i = -1;
	while (fc_arg->s_comp[++i])
	{
		eq = ft_strchri(fc_arg->s_comp[i], '=');
		what = ft_strndup(fc_arg->s_comp[i], eq);
		if (ft_strstr(cmd, what) == NULL)
		{
			free(what);
			continue ;
		}
		buf = insert_history_assignment(buf, buf_len, fc_arg->s_comp[i] + eq, what);
		printf("command to launch: %d -  %s\n", i, buf);
	}
	return (buf);
}

char				*insert_history_assignment(char *buf, int buf_len,
						char *change, char *what)
{
	int				ptr;
	int				len_what;
	int				len_change;
	int				len_cmd;

	ptr = ft_strstr(buf, what) - buf;
	len_cmd = ft_strlen(buf);
	len_change = ft_strlen(change);
	if (ptr == 0)
		return (insert_history_assignment_whole_line
			(buf, buf_len, change, len_change));
	len_what = ft_strlen(what);
	str_shift(buf + ptr, len_what * -1);
	if (len_cmd - len_what + len_change >= buf_len)
	{
		buf = ft_realloc(buf, len_cmd, buf_len, buf_len * 2);
		buf_len *= 2;
	}
	ft_strcpy(buf + ptr, change);
	return (buf);
}

char				*insert_history_assignment_whole_line(char *buf, int buf_len,
						char *change, int len_change)
{
	int				i;
	int				len_cmd;
	int				len_full;
	int				ptr;

	i = -1;
	ptr = 0;
	len_cmd = ft_strlen(buf);
	len_full = len_cmd;
	while (++i < len_cmd)
	{
		if (len_full + len_change >= buf_len)
		{
			buf = ft_realloc(buf, len_cmd, buf_len, buf_len * 2);
			buf_len *= 2;
		}
		ft_strcpy(buf + ptr, change);
		ptr += len_change;
		len_full += len_change;
	}
	return (buf);
}