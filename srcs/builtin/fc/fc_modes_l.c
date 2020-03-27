#include "shell42.h"
#include "builtin42.h"

int					btin_fc_list_mode(char **argv, int j, t_btin_fc **fc_arg,
						int *flags)
{
	int				i;

	if (g_hist.len < 1)
	{
		error_handler(VARIABLE_ERROR | (ERR_HISTORY_NUM << 9), "fc");
		return (HIST_ERROR);
	}
	i = btin_fc_list_check_line_args(argv, j, fc_arg, flags);
	if (i == HIST_ERROR)
		return (HIST_ERROR);
	if (argv[++i])
		return (btin_fc_list_check_other_args(&argv[i], fc_arg, flags));
	return (btin_fc_list_mode_no_args(fc_arg, flags));
}

int					btin_fc_list_check_line_args(char **argv, int j,
						t_btin_fc **fc_arg, int *flags)
{
	int				i;
	int				tmp;

	i = 0;
	while (argv[i][++j])
	{
		if ((tmp = btin_fc_save_editor(argv, i, j, fc_arg)) == HIST_ERROR)
			return (HIST_ERROR);
		else if (tmp == HIST_EXEC || tmp != i)
			return (i = (tmp == HIST_EXEC) ? i : tmp);
		if (argv[i][j] == 's')
			return (btin_fc_exec_mode(&argv[i], j, fc_arg, flags));
		if (btin_fc_other_flags(argv[i][j], flags) == HIST_ERROR)
			return (HIST_ERROR);
	}
	return (i);
}

int					btin_fc_list_check_other_args(char **argv,
						t_btin_fc **fc_arg, int *flags)
{
	int				i;
	int				tmp;

	i = -1;
	while (argv[++i])
	{
		if (argv[i][0] != '-' || (argv[i][0] == '-' && !argv[i][1]))
		{
			error_handler(VARIABLE_ERROR | (ERR_HISTORY_NUM << 9), "fc");
			return (HIST_ERROR);
		}
		if (argv[i][0] == '-' && argv[i][1] == '-' && !argv[i][2])
			return (btin_fc_list_nums_no_error(&argv[i + 1], fc_arg, flags));
		if (ft_isdigit(argv[i][0]) || (argv[i][0] == '-' && ft_isdigit(argv[i][1])))
		{
			return (btin_fc_list_mode_num_args(argv, i, fc_arg, flags) == HIST_ERROR ?
				HIST_ERROR : btin_fc_list_mode_flags_off(flags));
		}
		tmp = btin_fc_list_check_line_args(&argv[i], 0, fc_arg, flags);
		if (tmp == HIST_ERROR || tmp == HIST_EXEC)
			return (tmp);
		i = (tmp > i) ? tmp : i;
	}
	return (btin_fc_list_mode_no_args(fc_arg, flags));
}

int					btin_fc_list_nums_no_error(char **argv,
						t_btin_fc **fc_arg, int *flags)
{
	if (!argv[0])
		return (btin_fc_list_mode_no_args(fc_arg, flags));
	if (ft_isdigit(argv[0][0]) || (argv[0][0] == '-' && ft_isdigit(argv[0][1])))
	{
		return (btin_fc_list_mode_num_args(argv, 0, fc_arg, flags) == HIST_ERROR ?
			HIST_ERROR : btin_fc_list_mode_flags_off(flags));
	}
	error_handler(VARIABLE_ERROR | (ERR_HISTORY_NUM << 9), "fc");
	return (HIST_ERROR);
}

int					btin_fc_list_mode_num_args(char **argv, int i,
						t_btin_fc **fc_arg, int *flags)
{
	(*fc_arg)->flag |= ARG_FIRST;
	(*fc_arg)->first = ft_atoi(argv[i]);
	i++;
	if (!argv[i])
	{
		(*fc_arg)->flag |= ARG_SECOND;
		(*fc_arg)->last = -1;
		return ((btin_fc_two_ints__list(fc_arg, flags) == HIST_ERROR) ?
			HIST_ERROR : 0);
	}
	else if (!(ft_isdigit(argv[i][0]) || (argv[i][0] == '-' &&
		ft_isdigit(argv[i][1]))))
	{
		error_handler(VARIABLE_ERROR | (ERR_HISTORY_NUM << 9), "fc");
		return (HIST_ERROR);
	}
	(*fc_arg)->flag |= ARG_SECOND;
	(*fc_arg)->last = ft_atoi(argv[i]);
	return ((btin_fc_two_ints__list(fc_arg, flags) == HIST_ERROR) ?
		HIST_ERROR : 0);
}
