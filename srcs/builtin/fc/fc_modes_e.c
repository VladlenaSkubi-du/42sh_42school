#include "shell42.h"
#include "builtin42.h"

int					btin_fc_edit_mode(char **argv, t_btin_fc **fc_arg,
						int *flags)
{
	size_t			li;
	size_t			sy;

	if (g_hist.len > 0)
		delete_last_history_element();
	if (g_hist.len < 1 || g_hist.last < 0)
	{
		error_handler(VARIABLE_ERROR | (ERR_HISTORY_NUM << 9), "fc");
		return (HIST_ERROR);
	}
	if ((*fc_arg)->editor == NULL)
	{
		li = find_in_variables(g_shvar, &sy, "FCEDIT=");
		if (g_shvar[li][sy])
			(*fc_arg)->editor = &g_shvar[li][sy];
		else
			(*fc_arg)->editor = "vim";
	}
	return (btin_fc_edit_other_args(argv, fc_arg, flags));
}

int					btin_fc_edit_other_args(char **argv,
						t_btin_fc **fc_arg, int *flags)
{
	int				i;
	
	i = 0;
	if (!argv[i])
		return (btin_fc_edit_no_args(fc_arg, flags));
	if (ft_isdigit(argv[i][0]) || (argv[i][0] == '-' && ft_isdigit(argv[i][1])))
	{
		return ((btin_fc_edit_mode_num_args(argv, i, fc_arg, flags) == HIST_ERROR) ?
			HIST_ERROR : btin_fc_edit_mode_flags_off(flags));
	}
	else
	{
		error_handler(VARIABLE_ERROR | (ERR_HISTORY_NUM << 9), "fc");
		return (HIST_ERROR);
	}
	return (0);
}

int					btin_fc_edit_mode_num_args(char **argv, int i,
						t_btin_fc **fc_arg, int *flags)
{
	(*fc_arg)->flag |= ARG_FIRST;
	(*fc_arg)->first = ft_atoi(argv[i]);
	i++;
	if (!argv[i])
		return ((btin_fc_one_int__exec(fc_arg) == HIST_ERROR) ?
			HIST_ERROR : 0);
	else if (!(ft_isdigit(argv[i][0]) || (argv[i][0] == '-' &&
		ft_isdigit(argv[i][1]))))
	{
		error_handler(VARIABLE_ERROR | (ERR_HISTORY_NUM << 9), "fc");
		return (HIST_ERROR);
	}
	(*fc_arg)->flag |= ARG_SECOND;
	(*fc_arg)->last = ft_atoi(argv[i]);
	return ((btin_fc_two_ints__edit(fc_arg) == HIST_ERROR) ?
		HIST_ERROR : 0);
}

int					btin_fc_two_ints__edit(t_btin_fc **fc_arg)
{
	int				temp;

	if (!(((*fc_arg)->flag & ARG_FIRST) && ((*fc_arg)->flag & ARG_SECOND)))
		return (HIST_ERROR);
	temp = g_hist.last_fc - ((g_hist.last + 1 == g_hist.len) ?
		g_hist.len - 1 : g_hist.last) + 1;
	if ((*fc_arg)->last > 0 && ((*fc_arg)->last_buf =
		btin_fc_positive_int__exec((*fc_arg)->last, temp,
		g_hist.last_fc)) == HIST_ERROR)
		return (HIST_ERROR);
	else if ((*fc_arg)->last <= 0)
		(*fc_arg)->last_buf = btin_fc_negative_int__list((*fc_arg)->last);
	if ((*fc_arg)->first > 0 && ((*fc_arg)->first_buf =
		btin_fc_positive_int__exec((*fc_arg)->first, temp,
		g_hist.last_fc)) == HIST_ERROR)
		return (HIST_ERROR);
	else if ((*fc_arg)->first <= 0)
		(*fc_arg)->first_buf = btin_fc_negative_int__list((*fc_arg)->first);
	return (0);
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
