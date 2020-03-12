/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 17:34:28 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/12 20:41:59 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

int					btin_fc_route_execution(int flags, t_btin_fc *fc_arg)
{
	if (flags & FLAG_E)
	{
		printf("editor = %s\n", fc_arg->editor);
		if (fc_arg->flag & ARG_FIRST)
			printf("first = %d\n", fc_arg->first);
		if (fc_arg->flag & ARG_SECOND)
			printf("last = %d\n", fc_arg->last);
		if (flags & FLAG_R)
			printf("reverse");
	}
	else if (flags & FLAG_L)
	{
		if (fc_arg->flag & ARG_FIRST)
			printf("first = %d\n", fc_arg->first);
		if (fc_arg->flag & ARG_SECOND)
			printf("last = %d\n", fc_arg->last);
		if (flags & FLAG_R)
			printf("reverse");
		if (flags & FLAG_N)
			printf("without numbers");
		else
			printf("with numbers");
	}
	else if (flags & FLAG_S)
	{
		//печатает команду, которую запускает
		if (fc_arg->first != g_hist.last)
			printf("command = %s\n", g_hist.hist[fc_arg->first]);
		else
			printf("last command = %s\n", g_hist.hist[fc_arg->first]);
		if (fc_arg->s_comp)
			printf("assignment: %s\n", fc_arg->s_comp);
		if (fc_arg->s_cmd)
			printf("find command: %s\n", fc_arg->s_cmd);
	}
	return (0);
}