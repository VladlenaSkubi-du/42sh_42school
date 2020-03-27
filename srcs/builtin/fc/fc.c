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
		return (NONINERACTIVE);
	}
	fc_arg = init_btin_fc();
	flags = find_options(1, (char*[]){"elsrn"}, pos->ar_v);
	if (flags < 0)
		return (btin_return_exit_status());
	flags = 0;
	if (btin_fc_find_mode(pos->ar_v, &fc_arg, &flags) == HIST_ERROR)
		return (btin_return_exit_status());
	if (btin_fc_route_execution(fc_arg, flags, pos->envir) == HIST_ERROR)
		return (btin_return_exit_status());
	free(fc_arg);
	return (0);
}

int					btin_fc_find_mode(char **argv, t_btin_fc **fc_arg,
						int *flags)
{
	int				i;
	
	i = 0;
	while (argv[++i])
	{
		if (!(argv[i][0] == '-') || (argv[i][0] == '-' && ft_isdigit(argv[i][1])))
			return (btin_fc_edit_mode(&argv[i], fc_arg, flags));
		if (argv[i][0] == '-' && !argv[i][1])
		{
			error_handler(VARIABLE_ERROR | (ERR_HISTORY_NUM << 9), "fc");
			return (HIST_ERROR);
		}
		else if (argv[i][0] == '-' && argv[i][1] == '-' && !argv[i][2])
			break ;
		i = btin_fc_other_args(argv, i, fc_arg, flags);
		if (i == HIST_ERROR || i == HIST_EXEC)
			return (i);
	}
	return (btin_fc_edit_mode(&argv[i], fc_arg, flags));
}

int					btin_fc_other_args(char **argv, int i, t_btin_fc **fc_arg, int *flags)
{
	int				j;
	int				tmp;
	int				flag;

	j = 0;
	flag = 0;
	while (argv[i][++j])
	{
		if ((tmp = btin_fc_save_editor(argv, i, j, fc_arg)) == HIST_ERROR)
			return (HIST_ERROR);
		else if (tmp == HIST_EXEC || tmp != i)
			return (i = (tmp == HIST_EXEC) ? i : tmp);
		if (argv[i][j] == 's')
			return (btin_fc_exec_mode(&argv[i], j, fc_arg, flags));
		else if (argv[i][j] == 'l')
			flag = j;
		else if (btin_fc_other_flags(argv[i][j], flags) == HIST_ERROR)
			return (HIST_ERROR);
	}
	if (flag > 0)
		return (btin_fc_list_mode(&argv[i], j, fc_arg, flags));
	return (i);
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
