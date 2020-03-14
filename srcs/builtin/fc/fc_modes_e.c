/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_modes_e.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 19:24:05 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/14 20:15:37 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

int					btin_fc_edit_mode(char **argv, int *flags,
						t_btin_fc **fc_arg)
{
	int				i;
	size_t			li;
	size_t			sy;
	
	i = 0;
	delete_last_history_element();
	if ((*fc_arg)->editor == NULL)
	{
		li = find_in_variables(g_shvar, &sy, "FCEDIT=");
		if (g_shvar[li][sy])
			(*fc_arg)->editor = &g_shvar[li][sy];
		else
			(*fc_arg)->editor = "vim";
	}
	if (!argv[i])
	{
		(*fc_arg)->flag |= ARG_FIRST;
		(*fc_arg)->first_buf = g_hist.last;
		btin_fc_edit_mode_flags_off(flags);
		return (0);
	}
	if (ft_isdigit(argv[i][0]) || (argv[i][0] == '-' && ft_isdigit(argv[i][1])))
	{
		if (btin_fc_edit_mode_num_args(argv, i, flags, fc_arg) == HIST_ERROR)
			return (HIST_ERROR);
		btin_fc_edit_mode_flags_off(flags);
	}
	else
	{
		error_handler(VARIABLE_ERROR | (ERR_HISTORY << 9), "fc");
		return (HIST_ERROR);
	}
	return (0);
}

int					btin_fc_edit_mode_num_args(char **argv, int i,
						int *flags, t_btin_fc **fc_arg)
{
	(*fc_arg)->flag |= ARG_FIRST;
	(*fc_arg)->first = ft_atoi(argv[i]);
	i++;
	if (!argv[i])
	{
		(*fc_arg)->first_buf = btin_fc_one_int((*fc_arg)->first);
		return (0);
	}
	else if (!(ft_isdigit(argv[i][0]) || (argv[i][0] == '-' &&
		ft_isdigit(argv[i][1]))))
	{
		error_handler(VARIABLE_ERROR | (ERR_HISTORY << 9), "fc");
		return (HIST_ERROR);
	}
	(*fc_arg)->flag |= ARG_SECOND;
	(*fc_arg)->last = ft_atoi(argv[i]);
	btin_fc_two_ints(fc_arg);
	return (0);
}

int					btin_fc_edit_mode_flags_off(int *flags)
{
	if (*flags & FLAG_L)
		*flags &= ~FLAG_L;
	if (*flags & FLAG_S)
		*flags &= ~FLAG_S;
	if (!(*flags & FLAG_E))
		*flags |= FLAG_E;
	return (0);
}