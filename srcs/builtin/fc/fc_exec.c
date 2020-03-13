/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 17:34:28 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/13 09:59:21 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

int					btin_fc_route_execution(int flags, t_btin_fc *fc_arg)
{
	int				i;

	printf("HISTORY\n");
	i = -1;
	while (g_hist.hist[++i])
		printf("%d - %s\n", i + 1, g_hist.hist[i]);
	printf("FC_EXECUTION\n");
	
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
		//печатает команду, которую запускает
		if (fc_arg->flag & ARG_FIRST)
			printf("command number = %d, cmd = %s\n", fc_arg->first_buf, g_hist.hist[fc_arg->first_buf]);
		if (fc_arg->s_comp)
		{
			i = -1;
			while (fc_arg->s_comp[++i])
				printf("%d - assignment: %s\n", i + 1, fc_arg->s_comp[i]);
		}
		if (fc_arg->s_cmd)
			printf("find command: %s\n", fc_arg->s_cmd);
	}
	return (0);
}