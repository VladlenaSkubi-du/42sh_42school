/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_modes_l.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 17:19:41 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/14 20:40:19 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

int					btin_fc_list_mode(char **argv, int j, int *flags,
						t_btin_fc **fc_arg)
{
	int				i;
	int				tmp;

	i = 0;
	while (argv[i][++j])
	{
		if ((tmp = btin_fc_save_editor(argv, i, j, fc_arg)) == HIST_ERROR)
			return (HIST_ERROR);
		else if (tmp == HIST_EXEC)
		{
			j = 0;
			break ;
		}
		else if (tmp != i)
		{
			i = tmp;
			j = 0;
			break ;
		}
		if (argv[i][j] == 's')
			return (btin_fc_exec_mode(&argv[i], j, flags, fc_arg));
	}
	while (argv[++i])
	{
		if (ft_isdigit(argv[i][0]) || (argv[i][0] == '-' && ft_isdigit(argv[i][1])))
		{
			if (btin_fc_list_mode_num_args(argv, i, flags, fc_arg) == HIST_ERROR)
				return (HIST_ERROR);
			btin_fc_list_mode_flags_off(flags);
			return (0);
		}
		if (argv[i][0] != '-')
		{
			error_handler(VARIABLE_ERROR | (ERR_HISTORY << 9), "fc");
			return (HIST_ERROR);
		}
		j = 0;
		while (argv[i][++j])
		{
			if ((tmp = btin_fc_save_editor(argv, i, j, fc_arg)) == HIST_ERROR)
				return (HIST_ERROR);
			else if (tmp == HIST_EXEC)
			{
				j = 0;
				break ;
			}
			else if (tmp != i)
			{
				i = tmp;
				j = 0;
				break ;
			}
			if (argv[i][j] == 's')
				return (btin_fc_exec_mode(&argv[i], j, flags, fc_arg));
		}
	}
	return (btin_fc_list_mode_no_args(flags, fc_arg));
}

int					btin_fc_list_mode_no_args(int *flags, t_btin_fc **fc_arg)
{
	(*fc_arg)->flag |= ARG_FIRST;
	(*fc_arg)->flag |= ARG_SECOND;
	(*fc_arg)->last = -1;
	(*fc_arg)->first = -17;
	btin_fc_two_ints(fc_arg);
	btin_fc_list_mode_flags_off(flags);
	return (0);
}

int					btin_fc_list_mode_num_args(char **argv, int i,
						int *flags, t_btin_fc **fc_arg)
{
	(*fc_arg)->flag |= ARG_FIRST;
	(*fc_arg)->first = ft_atoi(argv[i]);
	i++;
	if (!argv[i])
	{
		(*fc_arg)->first_buf = btin_fc_one_int((*fc_arg)->first);
		(*fc_arg)->last_buf = btin_fc_one_int(-1);
		(*fc_arg)->last = g_hist.last_fc - 1;
		(*fc_arg)->first = ((*fc_arg)->last -
			((*fc_arg)->last_buf - (*fc_arg)->first_buf) < 1) ?
			g_hist.len + ((*fc_arg)->last -
			((*fc_arg)->last_buf - (*fc_arg)->first_buf)) :
			(*fc_arg)->last - ((*fc_arg)->last_buf - (*fc_arg)->first_buf);
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

int					btin_fc_list_mode_flags_off(int *flags)
{
	if (*flags & FLAG_E)
		*flags &= ~FLAG_E;
	else if (*flags & FLAG_S)
		*flags &= ~FLAG_S;
	return (0);
}
