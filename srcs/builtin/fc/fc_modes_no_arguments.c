/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_modes_no_arguments.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 17:48:53 by vladlenasku       #+#    #+#             */
/*   Updated: 2020/03/23 23:24:50 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

int					btin_fc_list_mode_no_args(t_btin_fc **fc_arg, int *flags)
{
	(*fc_arg)->flag |= ARG_FIRST;
	(*fc_arg)->flag |= ARG_SECOND;
	(*fc_arg)->last = -1;
	(*fc_arg)->first = -17;
	return (btin_fc_two_ints__list(fc_arg, flags) == HIST_ERROR ? 
		HIST_ERROR : btin_fc_list_mode_flags_off(flags));
}

int					btin_fc_exec_no_args(t_btin_fc **fc_arg, int *flags)
{
	(*fc_arg)->flag |= ARG_FIRST;
	(*fc_arg)->first_buf = g_hist.last;
	return (btin_fc_exec_mode_flags_off(flags));
}

int					btin_fc_edit_no_args(t_btin_fc **fc_arg, int *flags)
{
	(*fc_arg)->flag |= ARG_FIRST;
	(*fc_arg)->first_buf = g_hist.last;
	return (btin_fc_edit_mode_flags_off(flags));
}

/*
** Because of norm it is here
*/

int					btin_fc_exec_mode_add_comp(t_btin_fc **fc_arg, char *comp)
{
	static int		i;

	if (comp != NULL)
	{
		(*fc_arg)->s_comp[i] = comp;
		i++;
	}
	else
	{
		free((*fc_arg)->s_comp);
		i = 0;
	}
	return (0);
}