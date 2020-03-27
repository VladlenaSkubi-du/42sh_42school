#include "shell42.h"
#include "builtin42.h"

int					btin_fc_exec_mode(char **argv, int j, t_btin_fc **fc_arg,
						int *flags)
{
	int				i;

	if (g_hist.len > 0)
		delete_last_history_element();
	if (g_hist.len < 1)
	{
		error_handler(VARIABLE_ERROR | (ERR_HISTORY_EXEC << 9), "fc");
		return (HIST_ERROR);
	}
	i = btin_fc_exec_check_line_args(argv, j, fc_arg, flags);
	if (i == HIST_ERROR)
		return (HIST_ERROR);
	if (argv[++i])
		return (btin_fc_exec_check_other_args(&argv[i], fc_arg, flags));
	return (btin_fc_exec_no_args(fc_arg, flags));
}

int					btin_fc_exec_check_line_args(char **argv, int j,
						t_btin_fc **fc_arg, int *flags)
{
	int				i;
	int				tmp;

	i = 0;
	if (argv[i][0] != '-' && (tmp = ft_strchri(argv[i], '=')) >= 0)
		return (btin_fc_exec_mode_comp(&argv[i], fc_arg, flags));
	(argv[i][0] != '-') ? (*fc_arg)->s_cmd = argv[i] : 0;
	if (argv[i][0] != '-')
		return (btin_fc_exec_mode_flags_off(flags));
	while (argv[i][++j])
	{
		if ((tmp = btin_fc_save_editor(argv, i, j, fc_arg)) == HIST_ERROR)
			return (HIST_ERROR);
		else if (tmp == HIST_EXEC || tmp != i)
			return (i = (tmp == HIST_EXEC) ? i : tmp);
		if (argv[i][j] == 'r' || argv[i][j] == 'n' || argv[i][j] == 'l')
			continue;
		else if (!(argv[i][j] == 'r' || argv[i][j] == 'n' || argv[i][j] == 'l'))
		{
			error_handler(OPTIONS_REQUIRED | (ERR_BTIN_INVALID << 9), "fc");
			usage_btin("fc");
			return (HIST_ERROR);
		}
	}
	return (i);
}

int					btin_fc_exec_check_other_args(char **argv,
						t_btin_fc **fc_arg, int *flags)
{
	int				i;
	int				tmp;

	i = -1;
	while (argv[++i])
	{
		if (ft_isdigit(argv[i][0]) || (argv[i][0] == '-' &&
			ft_isdigit(argv[i][1])))
		{
			(*fc_arg)->flag |= ARG_FIRST;
			(*fc_arg)->first = ft_atoi(argv[i]);
			return ((btin_fc_one_int__exec(fc_arg) == HIST_ERROR) ?
				HIST_ERROR : btin_fc_exec_mode_flags_off(flags));
		}
		tmp = btin_fc_exec_check_invalid(&argv[i], fc_arg, flags);
		if (tmp == HIST_ERROR || tmp == HIST_EXEC)
			return (tmp);
		tmp = btin_fc_exec_check_line_args(&argv[i], 0, fc_arg, flags);
		if (tmp == HIST_ERROR || tmp == HIST_EXEC)
			return (tmp);
		i = (tmp > i) ? tmp : i;
	}
	return (btin_fc_exec_no_args(fc_arg, flags));
}

int					btin_fc_exec_mode_comp(char **argv,
						t_btin_fc **fc_arg, int *flags)
{
	int				i;
	int				tmp;

	i = -1;
	while (argv[++i])
	{
		if ((tmp = ft_strchri(argv[i], '=')) >= 0)
		{
			(!(*fc_arg)->s_comp) ? (*fc_arg)->s_comp =
				(char**)ft_xmalloc(sizeof(char*) * FC_COMP_ARRAY) : 0;
			btin_fc_exec_mode_add_comp(fc_arg, argv[i]);
			continue;
		}
		if (ft_isdigit(argv[i][0]) || (argv[i][0] == '-'
			&& ft_isdigit(argv[i][1])))
		{
			(*fc_arg)->flag |= ARG_FIRST;
			(*fc_arg)->first = ft_atoi(argv[i]);
			btin_fc_one_int__exec(fc_arg);
			return (btin_fc_exec_mode_flags_off(flags));
		}
		(*fc_arg)->s_cmd = argv[i];
		return (btin_fc_exec_mode_flags_off(flags));
	}
	return (btin_fc_exec_no_args(fc_arg, flags));
}

int					btin_fc_exec_check_invalid(char **argv,
						t_btin_fc **fc_arg, int *flags)
{
	int				i;

	i = 0;
	if (argv[i][0] == '-' && !argv[i][1])
	{
		error_handler(VARIABLE_ERROR | (ERR_HISTORY_NUM << 9), "fc");
		return (HIST_ERROR);
	}
	if (argv[i][0] == '-' && argv[i][1] == '-' && !argv[i][2])
		return (btin_fc_exec_mode_comp(&argv[i], fc_arg, flags));
	return (i);
}
