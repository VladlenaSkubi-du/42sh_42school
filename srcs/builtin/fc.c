/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 14:10:50 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/05 14:31:43 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

#define				FLAG_S 0x2
#define				FLAG_N 0x4
#define				FLAG_L 0x8
#define				FLAG_R 0x10
#define				FLAG_E 0x20

/*
** The process is the following:
** 1) we find if we in general have options
** 2) we unactivate options if they contradict
** 3) we start to find arguments for each option and check the other options
** that may contradict (s and e - the first met is executed, s and l - 
** the first met is executed)
*/

int                 btin_fc(int argc, char **argv, char **environ)
{
	int				flags;
	t_btin_fc		fc_arg;
	size_t			li;
	size_t			sy;

	li = find_in_variables(g_rdovar, &sy, "42SH_NONINTERACTIVE=");
	if (g_rdovar[li][sy] == '1')
		return (0);
	flags = 0;
	fc_arg = init_btin_fc();
	flags = find_options(1, (char*[]){"erlns"}, argv, 1);
	if ((flags & FLAG_N) && !(flags & FLAG_L))
		flags &= ~FLAG_N;
	if (flags != 1 && ((flags & FLAG_E) || (flags & FLAG_L) || (flags & FLAG_S)))
		btin_fc_fill_structure(argv, &flags, &fc_arg);
		// btin_fc_check_options(argv, &flags, &fc_arg);
	return (0);
}

int					btin_fc_fill_structure(char **argv, int *flags,
						t_btin_fc *fc_arg)
{
	int				i;
	int				j;
	
	i = 0;
	j = 0;
	while (argv[++i])
	{
		if (argv[i][0] != '-')
		{
			fc_arg->arg_e_first = ft_atoi(argv[i]);
		}
		while (argv[i][++j])
		{
			if (argv[i][j] == 'n' || argv[i][j] == 'r')
				continue ;
			(argv[i][1] && argv[i][1] == 'e') ? btin_fc_e_args(argv, i, j, &fc_arg) : 0;
			(argv[i][1] && argv[i][1] == 'l') ? btin_fc_l_args(argv, i, j, &fc_arg) : 0;
			(argv[i][1] && argv[i][1] == 's') ? btin_fc_s_args(argv, i, j, &fc_arg) : 0;
		}
	}
	return (0);
}

int					btin_fc_e_args(char **argv, int i, int j, t_btin_fc **fc_arg)
{
	return (0);
}

int					btin_fc_l_args(char **argv, int i, int j, t_btin_fc **fc_arg)
{
	t_btin_fc		*tmp;

	tmp = *fc_arg;
	tmp->arg_l_first = (argv[i + 1]) ? ft_atoi(argv[i + 1]) : tmp->arg_l_first;
	tmp->arg_l_last = (argv[i + 2]) ? ft_atoi(argv[i + 2]) : tmp->arg_l_last;
	if (tmp->arg_l_first == 0 && argv[i + 1] && argv[i + 1][0] != '0')
		tmp->arg_l_first = -17;
	if (tmp->arg_l_last == 0 && argv[i + 2] && argv[i + 2][0] != '0')
		tmp->arg_l_first = -1;
	// if (argv[i][j] == 'l' && (*flags & FLAG_S))
	// 			*flags &= ~FLAG_S; - если у л есть аргументы, он первый - он важнее, но если нет, идет к s
	//если он не может отработать по аргументам одно он лезет в другое ААААААА
	printf("%d - %d\n", tmp->arg_l_first, tmp->arg_l_last);
	return (0);
}

int					btin_fc_s_args(char **argv, int i, int j, t_btin_fc **fc_arg)
{
	return (0);
}
