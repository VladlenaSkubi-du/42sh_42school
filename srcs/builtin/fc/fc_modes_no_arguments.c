/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_modes_no_arguments.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 16:10:44 by sschmele          #+#    #+#             */
/*   Updated: 2020/09/07 21:27:54 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

/*
** For the list mode without arguments we print the last 16 commands
** from the history list. If there are less than 16 - as much
** as we have
*/

int					btin_fc_list_mode_no_args(t_btin_fc **fc_arg, int *flags)
{
	int				temp;

	temp = 0;
	(*fc_arg)->flag |= ARG_FIRST;
	(*fc_arg)->flag |= ARG_SECOND;
	(*fc_arg)->last = -1;
	(*fc_arg)->first = -17;
	return (btin_fc_two_ints__list(fc_arg, temp) == HIST_ERROR ?
		HIST_ERROR : btin_fc_list_mode_flags_off(flags));
}

/*
** Without arguments we invoke the last command from the history
** list
*/

int					btin_fc_exec_no_args(t_btin_fc **fc_arg, int *flags)
{
	(*fc_arg)->flag |= ARG_FIRST;
	(*fc_arg)->first_buf = g_hist.last;
	return (btin_fc_exec_mode_flags_off(flags));
}

/*
** Without arguments we invoke the last command from the history
** list
*/

int					btin_fc_edit_no_args(t_btin_fc **fc_arg, int *flags)
{
	(*fc_arg)->flag |= ARG_FIRST;
	(*fc_arg)->first_buf = g_hist.last;
	return (btin_fc_edit_mode_flags_off(flags));
}

int					btin_fc_error_message(int error, char *option)
{
	if (error == VARIABLE_ERROR)
		error_handler(VARIABLE_ERROR | (ERR_HISTORY_NUM << 9), "fc");
	else if (error == NONINERACTIVE)
	{
		error_handler(NONINERACTIVE, option);
		return (BTIN_ERROR);
	}
	return (HIST_ERROR);
}

int					fc_before_parser(char *cmd)
{
	int				li;
	int				sy;

	li = find_in_variable(&sy, "42SH_NONINTERACTIVE");
	g_envi[li][sy] = '1';
	parser(cmd);
	li = find_in_variable(&sy, "42SH_NONINTERACTIVE");
	g_envi[li][sy] = '0';
	return (0);
}
