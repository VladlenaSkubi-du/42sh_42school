/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 14:10:50 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/14 20:13:21 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

/*
** The process is the following:
** 1) we find if we in general have options
** 2) we unactivate options if they contradict
** 3) we start to parse arguments for each option and check the other options
** that may contradict
** There are 3 main options: edit and exec (e), list (l) and exec only (s)
** Starting from the beginning of line if one option had all the arguments
** to start, everything after is ignored
*/

int                 btin_fc(int argc, char **argv, char **environ)
{
	int				flags;
	t_btin_fc		*fc_arg;
	size_t			li;
	size_t			sy;

	li = find_in_variables(g_rdovar, &sy, "42SH_NONINTERACTIVE=");
	if (g_rdovar[li][sy] == '1')
		return (0);
	flags = 0;
	fc_arg = init_btin_fc();
	flags = find_options(1, (char*[]){"elsrn"}, argv, 1);
	if (flags < 1)
		return (0);
		
	printf("flags are: ");
	if (flags & FLAG_E)
		printf("-e\n");
	if (flags & FLAG_L)
		printf("-l\n"); 
	if (flags & FLAG_S)
		printf("-s\n");
	
	if ((flags & FLAG_N) && !(flags & FLAG_L))
		flags &= ~FLAG_N;
	if (btin_fc_find_mode(argv, argc, &flags, &fc_arg) == HIST_ERROR)
		return (0);
	btin_fc_route_execution(flags, fc_arg);
	//btin_fc_exec_mode_add_comp(fc_arg, NULL); - добавить в exec
	free(fc_arg);
	return (0);
}

int					btin_fc_find_mode(char **argv, int argc, int *flags,
						t_btin_fc **fc_arg)
{
	int				i;
	int				j;
	int				tmp;
	int				flag;
	
	i = 0;
	tmp = -1;
	flag = 0;
	while (argv[++i])
	{
		if (!(argv[i][0] == '-') || (argv[i][0] == '-' && ft_isdigit(argv[i][1])))
			return (btin_fc_edit_mode(&argv[i], flags, fc_arg));
		j = 0;
		if (!argv[i][j + 1])
		{
			error_handler(VARIABLE_ERROR | (ERR_HISTORY << 9), "fc");
			return (HIST_ERROR);
		}
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
			else if (argv[i][j] == 'l')
				flag = j;
		}
		if (flag > 0)
			return (btin_fc_list_mode(&argv[i], j, flags, fc_arg));
	}
	return (btin_fc_edit_mode(&argv[i], flags, fc_arg));
}

int					btin_fc_save_editor(char **argv, int i,
						int j, t_btin_fc **fc_arg)
{
	if (argv[i][j] == 'e' && !(argv[i + 1] || argv[i][j + 1]))
	{
		error_handler(OPTIONS_REQUIRED | (ERR_BTIN_ARG << 9), "fc: -e");
		usage_btin("fc");
		return (HIST_ERROR);
	}
	else if (argv[i][j] == 'e' && (argv[i + 1] || argv[i][j + 1]))
	{
		if (argv[i][j + 1])
		{
			(*fc_arg)->editor = &argv[i][j + 1];
			return (HIST_EXEC);
		}
		else
		{
			i++;
			(*fc_arg)->editor = argv[i];
		}
	}
	return (i);
} 

int					btin_fc_one_int(int value)
{
	int				final_buf;

	final_buf = g_hist.last;
	if (value <= 0)
	{
		value = (value == 0) ? -1 : value;
		final_buf += value;
		if (final_buf < 0)
			final_buf = 0;
	}
	else if (value > 0)
	{
		if (value - 1 > 0 && value - 1 < g_hist.last)
			final_buf = value - 1; //было -1
	}
	return (final_buf);
}

int					btin_fc_two_ints(t_btin_fc **fc_arg)
{
	t_btin_fc		*tmp;

	tmp = *fc_arg;
	if (!((tmp->flag & ARG_FIRST) && (tmp->flag & ARG_SECOND)))
		return (0);
	tmp->last_buf = btin_fc_one_int(tmp->last);
	tmp->last = g_hist.last_fc - 1;
	tmp->first_buf = btin_fc_one_int(tmp->first);
	tmp->first = (tmp->last - (tmp->last_buf - tmp->first_buf) < 1) ?
		g_hist.len + (tmp->last - (tmp->last_buf - tmp->first_buf)) :
		tmp->last - (tmp->last_buf - tmp->first_buf);
	return (0);
}
