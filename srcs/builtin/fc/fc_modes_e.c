#include "shell42.h"
#include "builtin42.h"

int					btin_fc_edit_mode(char **argv, t_btin_fc **fc_arg,
						int *flags) //проверить на другие флаги, больше тестов
{
	size_t			li;
	size_t			sy;

	if (g_hist.len > 0)
		delete_last_history_element();
	if (g_hist.len < 1)
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
	{
		(*fc_arg)->first_buf = btin_fc_one_int__edit((*fc_arg)->first);
		return (0);
	}
	else if (!(ft_isdigit(argv[i][0]) || (argv[i][0] == '-' &&
		ft_isdigit(argv[i][1]))))
	{
		error_handler(VARIABLE_ERROR | (ERR_HISTORY_NUM << 9), "fc");
		return (HIST_ERROR);
	}
	(*fc_arg)->flag |= ARG_SECOND;
	(*fc_arg)->last = ft_atoi(argv[i]);
	btin_fc_two_ints__edit(fc_arg);
	return (0);
}

int					btin_fc_one_int__edit(int value)
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
			final_buf = value - 1;
		else
			final_buf = (g_hist.last > 0) ? final_buf - 1 : 0;
	}
	return (final_buf);
}

int					btin_fc_two_ints__edit(t_btin_fc **fc_arg)
{
	t_btin_fc		*tmp;

	tmp = *fc_arg;
	if (!((tmp->flag & ARG_FIRST) && (tmp->flag & ARG_SECOND)))
		return (0);
	tmp->last_buf = btin_fc_one_int__edit(tmp->last);
	tmp->first_buf = btin_fc_one_int__edit(tmp->first);
	return (0);
}
