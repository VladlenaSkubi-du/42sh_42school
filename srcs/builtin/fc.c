/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 14:10:50 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/05 20:30:31 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

#define				HIST_ERROR -1
#define				HIST_EXEC 1
#define				FLAG_S 0x2
#define				FLAG_N 0x4
#define				FLAG_L 0x8
#define				FLAG_R 0x10
#define				FLAG_E 0x20

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
	int				tmp;

	li = find_in_variables(g_rdovar, &sy, "42SH_NONINTERACTIVE=");
	if (g_rdovar[li][sy] == '1')
		return (0);
	flags = 0;
	fc_arg = init_btin_fc();
	flags = find_options(1, (char*[]){"erlns"}, argv, 1);
	if ((flags & FLAG_N) && !(flags & FLAG_L))
		flags &= ~FLAG_N;
	if (flags != 1 && ((flags & FLAG_E) || (flags & FLAG_L) || (flags & FLAG_S)))
	{
		tmp = btin_fc_fill_structure(argv, &flags, &fc_arg);
		if (tmp == HIST_ERROR)
			return (0);
	}
	else
	{
		tmp = btin_fc_no_args(argv, &fc_arg, flags);
		if (tmp == HIST_ERROR)
			return (0);
	}
	free(fc_arg);
	return (0);
}

int					btin_fc_fill_structure(char **argv, int *flags,
						t_btin_fc **fc_arg)
{
	int				i;
	int				tmp;
	
	i = 0;
	while (argv[++i])
	{
		if (argv[i][0] != '-' || (argv[i][0] == '-' && ft_isdigit(argv[i][1]))) //только числа
		{
			tmp = btin_fc_no_args(&argv[i], fc_arg, *flags);
			return ((tmp == HIST_ERROR) ? HIST_ERROR : HIST_EXEC);
		}
		tmp = 0;	
		while (!(argv[i][tmp] == 'e' || argv[i][tmp] == 'l' || argv[i][tmp] == 's'))
			tmp++;
		if (argv[i][tmp] == 'e')
		{
			tmp = btin_fc_e_args(&argv[i], tmp, fc_arg);
			return ((tmp == HIST_ERROR) ? HIST_ERROR : HIST_EXEC);
		}
		if (argv[i][tmp] == 'l')
		{
			tmp = btin_fc_l_args(&argv[i], tmp, fc_arg);
			return ((tmp == HIST_ERROR) ? HIST_ERROR : HIST_EXEC);
		}
		if (argv[i][tmp] == 's')
		{
			tmp = btin_fc_s_args(&argv[i], tmp, fc_arg);
			return ((tmp == HIST_ERROR) ? HIST_ERROR : HIST_EXEC);
		}
	}
	return (0);
}

/*
** There can be no more than 2 arguments and in our program no arguments is an
** edit (e) mode.
** From the very beginning here comes only digits and other signs except of '-'
*/

int					btin_fc_no_args(char **argv, t_btin_fc **fc_arg, int flags)
{
	int				i;
	t_btin_fc		*tmp;

	tmp = *fc_arg;
	i = -1;
	while (argv[++i])
	{
		if (!(ft_isdigit(argv[i][0]) || (argv[i][0] == '-' && argv[i][1]
			&& ft_isdigit(argv[i][1]))))
		{
			error_handler(VARIABLE_ERROR | (ERR_HISTORY << 9), "fc");
			return (HIST_ERROR);
		}
		tmp->arg_e_first = (i == 0) ? ft_atoi(argv[i]) : tmp->arg_e_first;
		tmp->arg_e_last = (i == 1) ? ft_atoi(argv[i]) : tmp->arg_e_last;
		if (i > 1)
			return (HIST_EXEC);
	}
	return (HIST_EXEC);
}

int					btin_fc_e_args(char **argv, int j, t_btin_fc **fc_arg)
{
	t_btin_fc		*tmp;
	int				i;
	size_t			li;
	size_t			sy;

	tmp = *fc_arg;
	i = 0;
	if (argv[i][j + 1])
		tmp->editor = &argv[i][j + 1];
	else if (!argv[i][j + 1] && argv[i + 1] && !(argv[i + 1][0] == '-'))
		tmp->editor = argv[i + 1];
	else
	{
		li = find_in_variables(g_shvar, &sy, "FCEDIT=");
		if (g_rdovar[li][sy])
			tmp->editor = &g_rdovar[li][sy];
		else
			tmp->editor = "vim";
	}
	//поставить проверку на аргументы
	return (HIST_EXEC);
}

int					btin_fc_l_args(char **argv, int j, t_btin_fc **fc_arg)
{
	t_btin_fc		*tmp;

	tmp = *fc_arg;
	// tmp->arg_l_first = (argv[i + 1]) ? ft_atoi(argv[i + 1]) : tmp->arg_l_first;
	// tmp->arg_l_last = (argv[i + 2]) ? ft_atoi(argv[i + 2]) : tmp->arg_l_last;
	// if (tmp->arg_l_first == 0 && argv[i + 1] && argv[i + 1][0] != '0')
	// 	tmp->arg_l_first = -17;
	// if (tmp->arg_l_last == 0 && argv[i + 2] && argv[i + 2][0] != '0')
	// 	tmp->arg_l_first = -1;
	// // if (argv[i][j] == 'l' && (*flags & FLAG_S))
	// // 			*flags &= ~FLAG_S; - если у л есть аргументы, он первый - он важнее, но если нет, идет к s
	// //если он не может отработать по аргументам одно он лезет в другое ААААААА
	// printf("%d - %d\n", tmp->arg_l_first, tmp->arg_l_last);
	return (0);
}

int					btin_fc_s_args(char **argv, int j, t_btin_fc **fc_arg)
{
	return (0);
}
