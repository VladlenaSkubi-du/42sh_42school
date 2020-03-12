/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_modes_e.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 19:24:05 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/12 20:40:50 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

int					btin_fc_edit_mode(char **argv, int *flags,
						t_btin_fc **fc_arg)
{
	int				i;
	
	i = 0;
	if (!argv[i])
	{
		(*fc_arg)->flag |= ARG_FIRST;
		(*fc_arg)->first_buf = btin_fc_one_int(-1);
		btin_fc_edit_mode_flags_off(flags);
	}
	if (ft_isdigit(argv[i][0]) || (argv[i][0] == '-' && ft_isdigit(argv[i][1])))
	{
		if (btin_fc_list_mode_num_args(argv, i, flags, fc_arg) == HIST_ERROR)
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

int					btin_fc_edit_mode_flags_off(int *flags)
{
	if (*flags & FLAG_L)
		*flags &= ~FLAG_L;
	else if (*flags & FLAG_S)
		*flags &= ~FLAG_S;
	return (0);
}