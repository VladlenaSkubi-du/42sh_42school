/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@sdudent.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 14:10:50 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/20 18:28:33 by rbednar          ###   ########.fr       */
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

int                 btin_fc(t_ltree *pos)
{
	int				flags;
	t_btin_fc		*fc_arg;
	size_t			li;
	size_t			sy;

	li = find_in_variables(g_rdovar, &sy, "42SH_NONINTERACTIVE");
	if (g_rdovar[li][sy] == '1')
	{
		error_handler(NONINERACTIVE, pos->ar_v[0]);
		return (0);
	}
	flags = 0;
	fc_arg = init_btin_fc();
	flags = find_options(1, (char*[]){"elsrn"}, pos->ar_v);
		
	printf("flags are: ");
	if (flags & FLAG_E)
		printf("-e\n");
	if (flags & FLAG_L)
		printf("-l\n"); 
	if (flags & FLAG_S)
		printf("-s\n");
	
	if ((flags & FLAG_N) && !(flags & FLAG_L))
		flags &= ~FLAG_N;
	if (btin_fc_find_mode(pos->ar_v, pos->ar_c, &flags, &fc_arg) == HIST_ERROR)
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
