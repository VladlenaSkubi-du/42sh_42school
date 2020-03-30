#include "shell42.h"
#include "builtin42.h"

int					btin_fc_route_execution(t_btin_fc *fc_arg, int flags,
						char **envir)
{

	if (flags & FLAG_E)
		return (btin_fc_execute_edition(fc_arg, flags, envir));
	else if (flags & FLAG_L)
	{
		if (flags & FLAG_R)
		{
			if (fc_arg->first_buf > fc_arg->last_buf)
				btin_fc_execute_list(fc_arg, flags, 'r');
			else
				btin_fc_execute_list_reverse(fc_arg, flags, 'r');
		}
		else
			if (fc_arg->first_buf > fc_arg->last_buf)
				btin_fc_execute_list_reverse(fc_arg, flags, 'd');
			else
				btin_fc_execute_list(fc_arg, flags, 'd');	
	}
	else if (flags & FLAG_S)
		return (btin_fc_execute_execution(fc_arg, flags));
	return (0);
}

int					btin_fc_execute_edition(t_btin_fc *fc_arg,
						int flags, char **envir)
{
	char			*tmpfile;
	int				fd;
	t_ltree			*sub;
	int				tmp;

	fd = ft_tmpfile_fc("tmp42sh_fc_XXXXXX", &tmpfile);
	if (fd < 0)
	{
		error_handler(TMPFILE, NULL);
		return (HIST_ERROR);
	}
	btin_fc_write_to_tmpfile(fc_arg, flags, fd);
	close(fd);
	sub = btin_fc_before_exec(fc_arg, envir, tmpfile);
	btin_fc_save_parser_globals(1);
	tmp = exec_init(sub);
	ft_arrdel(sub->ar_v);
	free(sub);
	btin_fc_save_parser_globals(0);
	if (tmp == 0)
		btin_fc_read_from_tmpfile(tmpfile);
	unlink(tmpfile);
	free(tmpfile);
	return ((tmp == 0) ? 0 : HIST_ERROR);
}

int					btin_fc_execute_execution(t_btin_fc *fc_arg, int flags)
{
	char			*cmd;
	int				tmp;

	cmd = NULL;
	if (fc_arg->s_cmd)
	{
		if ((tmp = find_in_history(fc_arg->s_cmd)) == -1)
		{
			error_handler(VARIABLE_ERROR | (ERR_HISTORY_EXEC << 9), fc_arg->s_cmd);
			return (HIST_ERROR);
		}
		cmd = ft_strdup(g_hist.hist[tmp]);
	}
	else if (fc_arg->flag & ARG_FIRST)
	{
		cmd = ft_strdup((g_hist.last >= fc_arg->first_buf) ?
			g_hist.hist[fc_arg->first_buf] : g_hist.hist[g_hist.last]);
	}
	if (fc_arg->s_comp)
		cmd = make_history_assignments(fc_arg, cmd);
	tmp = ft_strlen(cmd);
	cmd = (tmp > 0 && cmd[tmp - 1] == '\n') ? cmd : ft_strrejoin(cmd, "\n");
	btin_fc_save_parser_globals(1);
	ft_putstr_fd(cmd, STDOUT_FILENO);
	parser(cmd);
	btin_fc_save_parser_globals(0);
	return (0);
}

int					btin_fc_execute_list_reverse(t_btin_fc *fc_arg, int flags, int flag)
{
	int				i;
	int				tmp;
	int				value;
	int				to;
	int				num;
	
	i = 0;
	value = (flag == 'd') ? fc_arg->first_buf : fc_arg->last_buf;
	to = (flag == 'd') ? fc_arg->last_buf : fc_arg->first_buf;
	num = (flag == 'd') ? fc_arg->first : fc_arg->last;
	while (value - i >= to && value - i >= 0)
	{
		tmp = ft_strlen(g_hist.hist[value - i]);
		if (tmp > 0 && g_hist.hist[value - i][tmp - 1] == '\n')
			tmp -= 1;
		if (!(flags & FLAG_N))
			ft_printf("%d\t%.*s\n", num - i, tmp,
				g_hist.hist[value - i]);
		else
			ft_printf("\t%.*s\n", tmp, g_hist.hist[value - i]);
		i++;
	}
	return (0);
}

int					btin_fc_execute_list(t_btin_fc *fc_arg, int flags, int flag)
{
	int				i;
	int				tmp;
	int				value;
	int				to;
	int				num;
	
	i = 0;
	value = (flag == 'd') ? fc_arg->first_buf : fc_arg->last_buf;
	to = (flag == 'd') ? fc_arg->last_buf : fc_arg->first_buf;
	num = (flag == 'd') ? fc_arg->first : fc_arg->last;
	while (value + i <= to && value + i < g_hist.len)
	{
		tmp = ft_strlen(g_hist.hist[value + i]);
		if (tmp > 0 && g_hist.hist[value + i][tmp - 1] == '\n')
			tmp -= 1;
		if (!(flags & FLAG_N))
			ft_printf("%d\t%.*s\n", num + i, tmp,
				g_hist.hist[value + i]);
		else
			ft_printf("\t%.*s\n", tmp, g_hist.hist[value + i]);
		i++;
	}
	return (0);
}