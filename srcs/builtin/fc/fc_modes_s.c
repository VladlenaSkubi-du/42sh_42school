/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_modes_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 17:56:18 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/13 11:21:51 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

int					btin_fc_exec_mode(char **argv, int *flags,
						t_btin_fc **fc_arg)
{
	int				i;
	int				tmp;

	i = 1;
	if (!argv[i])
		return (btin_fc_exec_mode_no_args(flags, fc_arg));
	if ((tmp = btin_fc_save_editor(argv, i, fc_arg)) == HIST_ERROR)
		return (HIST_ERROR);
	else if (tmp != i)
		return (btin_fc_exec_mode(&argv[tmp], flags, fc_arg));
	return (btin_fc_exec_mode_proc(&argv[i], flags, fc_arg));
}

int					btin_fc_exec_mode_no_args(int *flags, t_btin_fc **fc_arg)
{
	(*fc_arg)->flag |= ARG_FIRST;
	(*fc_arg)->first_buf = g_hist.last;
	btin_fc_exec_mode_flags_off(flags);
	return (0);
}

int					btin_fc_exec_mode_flags_off(int *flags)
{
	if (*flags & FLAG_E)
		*flags &= ~FLAG_E;
	else if (*flags & FLAG_L)
		*flags &= ~FLAG_L;
	else if (*flags & FLAG_R)
		*flags &= ~FLAG_R;
	return (0);
}

int					btin_fc_exec_mode_proc(char **argv, int *flags,
						t_btin_fc **fc_arg)
{
	char			*tmp;
	int				i;

	i = -1;
	while (argv[++i])
	{
		if (ft_isdigit(argv[i][0]) || (argv[i][0] == '-' &&
			ft_isdigit(argv[i][1])))
		{
			(*fc_arg)->flag |= ARG_FIRST;
			(*fc_arg)->first = ft_atoi(argv[i]);
			(*fc_arg)->first_buf = btin_fc_one_int((*fc_arg)->first);
			return (btin_fc_exec_mode_flags_off(flags));
		}
		if ((tmp = ft_strchr(argv[i], '=')) != NULL)
		{
			(!(*fc_arg)->s_comp) ? (*fc_arg)->s_comp =
				(char**)ft_xmalloc(sizeof(char*) * FC_COMP_ARRAY) : 0;
			btin_fc_exec_mode_add_comp(fc_arg, argv[i]);
			continue;
		}
		(*fc_arg)->s_cmd = argv[i];
		return (0);
	}
	return (0);
}

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