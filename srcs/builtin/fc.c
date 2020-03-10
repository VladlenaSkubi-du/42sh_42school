/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 14:10:50 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/10 18:11:48 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

#define				HIST_ERROR -1
#define				HIST_EXEC 0
#define				HIST_SEARCH 1

#define				FLAG_N 0x2
#define				FLAG_R 0x4
#define				FLAG_S 0x8
#define				FLAG_L 0x10
#define				FLAG_E 0x20
#define				ARG_FIRST 0x1
#define				ARG_SECOND 0x2

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
	free(fc_arg);
	return (0);
}

int					btin_fc_find_mode(char **argv, int argc, int *flags,
						t_btin_fc **fc_arg)
{
	int				i;
	int				j;
	
	i = 1;
	j = 0;
	if (argv[i][0] && !(argv[i][0] == '-'))
		return (btin_fc_edit_mode(&argv[i], flags, fc_arg));
	while (argv[i][++j])
	{
		if (argv[i][j] == 'e' && argc == (i + 1) && !argv[i][j + 1])
		{
			error_handler(OPTIONS_REQUIRED | (ERR_BTIN_ARG << 9), "fc: -e");
			return (HIST_ERROR);
		}
		else if (argv[i][j] == 'e' && ((argc > (i + 1) || argv[i][j + 1])))
			if ((i = btin_fc_save_editor(argv, i, fc_arg)) < argc)
				return (btin_fc_find_mode(&argv[i], argc, flags, fc_arg));
	}
	if (argv[i][j - 1] == 's')
		return (btin_fc_exec_mode(&argv[i], flags, fc_arg));
	else if (argv[i][j - 1] == 'l')
		return (btin_fc_list_mode(&argv[i], flags, fc_arg));
	return (btin_fc_edit_mode(&argv[i], flags, fc_arg));
}

int					btin_fc_edit_mode(char **argv, int *flags,
						t_btin_fc **fc_arg)
{
	
	return (0);
}

int					btin_fc_list_mode(char **argv, int *flags, t_btin_fc **fc_arg)
{
	int				i;

	i = 1;
	if (!argv[i])
	{
		(*fc_arg)->flag |= ARG_FIRST;
		(*fc_arg)->flag |= ARG_SECOND;
		(*fc_arg)->last = g_hist.last;
		(*fc_arg)->first = (g_hist.last - POSIX_FC_DIFF > 0) ? 
			g_hist.last - POSIX_FC_DIFF : 0;
		if (*flags & FLAG_E)
			*flags &= ~FLAG_E;
		else if (*flags & FLAG_S)
			*flags &= ~FLAG_E;
		return (0);
	}
	if (argv[i][0] == '-' && argv[i][1] == 'e' && !(argv[i][2] || argv[i + 1]))
	{
		error_handler(OPTIONS_REQUIRED | (ERR_BTIN_ARG << 9), "fc: -e");
		return (HIST_ERROR);
	}
	else if (argv[i][0] == '-' && argv[i][1] == 'e')
	{
		i = btin_fc_save_editor(argv, i, fc_arg);
		return (btin_fc_list_mode(&argv[i], flags, fc_arg));
	}
	if (argv[i][0] == '-' && argv[i][1] == 's')
		return (btin_fc_exec_mode(&argv[i], flags, fc_arg));
	if (ft_isdigit(argv[i][0]) || (argv[i][0] == '-' && ft_isdigit(argv[i][1])))
	{
		(*fc_arg)->flag |= ARG_FIRST;
		(*fc_arg)->first = ft_atoi(argv[i]);
		i++;
		if (!argv[i])
		{
			(*fc_arg)->first = btin_fc_one_int((*fc_arg)->first);
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
	return (0);
}

int					btin_fc_exec_mode(char **argv, int *flags, t_btin_fc **fc_arg)
{
	return (0);
}

int					btin_fc_save_editor(char **argv, int i, t_btin_fc **fc_arg)
{
	if (argv[i][2])
		(*fc_arg)->editor = &argv[i][2];
	else
	{
		i++;
		(*fc_arg)->editor = argv[i];
	}
	return (i);
} 

int					btin_fc_one_int(int value)
{
	int				final;
	int				temp;
	int				start;

	temp = 0;
	final = g_hist.last_fc;
	if (value < 0)
	{
		final += value;
	}
		return (g_hist.last + value);
	if (value < g_hist.last)
		return (value);
	return (final);
}

int					btin_fc_two_ints(t_btin_fc **fc_arg)
{
	t_btin_fc		*tmp;
	

	tmp = *fc_arg;
	if (!((tmp->flag & ARG_FIRST) && (tmp->flag & ARG_SECOND)))
		return (0);
	if (tmp->first < 0)
		tmp->first = btin_fc_one_int(tmp->first);
	return (0);
}

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
