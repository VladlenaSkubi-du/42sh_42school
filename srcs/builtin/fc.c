/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 14:10:50 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/04 20:11:54 by sschmele         ###   ########.fr       */
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
	if (flags != 1)
		btin_fc_check_options(argv, &flags, &fc_arg);
	return (0);
}

t_btin_fc			init_btin_fc(void)
{
	t_btin_fc		fc;

	fc.editor = "vim";
	fc.arg_l_first = -17;
	fc.arg_l_first = -1;
	fc.arg_s_comp = NULL;
	fc.arg_s_first = -1;
	return (fc);
}

int					btin_fc_check_options(char **argv, int *flags,
						t_btin_fc *fc_arg)
{
	if ((*flags & FLAG_E) && (*flags & FLAG_L))
		*flags &= ~FLAG_E;
	if ((*flags & FLAG_E) && (*flags & FLAG_S))
		*flags &= ~FLAG_E;
	if ((*flags & FLAG_N) && !(*flags & FLAG_L))
		*flags &= ~FLAG_N;
	if (!((*flags & FLAG_E) || (*flags & FLAG_L) || (*flags & FLAG_S)))
		return (0);
	btin_fc_fill_structure(argv, flags, &fc_arg);
	return (0);
}

int					btin_fc_fill_structure(char **argv, int *flags,
						t_btin_fc **fc_arg)
{
	int				i;
	int				j;
	
	i = 0;
	j = 0;
	while (argv[++i])
	{
		if (argv[i][0] != '-')
			continue ;
		while (argv[i][++j])
		{
			if (argv[i][j] == 'l' && argv[i][j + 1] && argv[i][j + 1] == 's')
				*flags &= ~FLAG_L;
			else if (argv[i][j] == 'l' && (*flags & FLAG_S))
				*flags &= ~FLAG_S;
			else if (argv[i][j] == 's' && (*flags & FLAG_L))
				*flags &= ~FLAG_L;
			if (argv[i][j] == 'l')
				btin_fc_l_args(argv, i, fc_arg);
		}
	}
	return (0);
}

int					btin_fc_l_args(char **argv, int i, t_btin_fc **fc_arg)
{
	t_btin_fc		*tmp;

	tmp = *fc_arg;
	tmp->arg_l_first = (argv[i + 1]) ? ft_atoi(argv[i + 1]) : tmp->arg_l_first;
	tmp->arg_l_last = (argv[i + 2]) ? ft_atoi(argv[i + 2]) : tmp->arg_l_last;
	if (tmp->arg_l_first == 0 && argv[i + 1] && argv[i + 1][0] != '0')
		tmp->arg_l_first = -17;
	if (tmp->arg_l_last == 0 && argv[i + 2] && argv[i + 2][0] != '0')
		tmp->arg_l_first = -1;
	//если он не может отработать по аргументам одно он лезет в другое ААААААА
	printf("%d - %d\n", tmp->arg_l_first, tmp->arg_l_last);
	return (0);
}
