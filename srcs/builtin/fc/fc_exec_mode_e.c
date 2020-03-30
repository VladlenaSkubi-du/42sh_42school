#include "shell42.h"
#include "builtin42.h"

int					btin_fc_read_from_tmpfile(char *tmpfile)
{
	char			*cmd;
	int				fd;
	
	fd = open(tmpfile, O_RDONLY);
	if (fd < 0)
	{
		error_handler(TMPFILE, NULL);
		return (HIST_ERROR);
	}
	btin_fc_save_parser_globals(1);
	while (ft_gnl(fd, &cmd))
	{
		ft_putendl_fd(cmd, STDOUT_FILENO);
		parser(cmd);
	}
	btin_fc_save_parser_globals(0);
	close(fd);
	return (0);
}

t_ltree				*btin_fc_before_exec(t_btin_fc *fc_arg,
						char **envir, char *tmpfile)
{
	t_ltree			*sub;

	sub = (t_ltree *)ft_xmalloc(sizeof(t_ltree));
	ltree_init(sub);
	sub->envir = envir;
	sub->ar_v = (char**)ft_xmalloc(sizeof(char*) * (2 + 1));
	sub->ar_v[0] = ft_strdup(fc_arg->editor);
	sub->ar_v[1] = ft_strdup(tmpfile);
	sub->ar_c = 2;
	return (sub);
}

int					btin_fc_write_to_tmpfile(t_btin_fc *fc_arg,
						int flags, int fd)
{
	int				tmp;

	if ((fc_arg->flag & ARG_FIRST) && !(fc_arg->flag & ARG_SECOND))
	{
		tmp = ft_strlen(g_hist.hist[fc_arg->first_buf]);
		if (tmp > 0 && g_hist.hist[fc_arg->first_buf][tmp - 1] == '\n')
			tmp -= 1;
		ft_putnendl_fd(g_hist.hist[fc_arg->first_buf], tmp, fd);
		return (0);
	}
	if (flags & FLAG_R)
	{
		if (fc_arg->first_buf > fc_arg->last_buf)
			btin_fc_execute_edit(fc_arg, flags, fd, 'r');
		else
			btin_fc_execute_edit_reverse(fc_arg, flags, fd, 'r');
	}
	else
	{
		if (fc_arg->first_buf > fc_arg->last_buf)
			btin_fc_execute_edit_reverse(fc_arg, flags, fd, 'd');
		else
			btin_fc_execute_edit(fc_arg, flags, fd, 'd');
	}
	return (0);
}

int					btin_fc_execute_edit_reverse(t_btin_fc *fc_arg,
						int flags, int fd, int flag)
{
	int				i;
	int				tmp;
	int				value;
	int				to;
	
	i = 0;
	value = (flag == 'd') ? fc_arg->first_buf : fc_arg->last_buf;
	to = (flag == 'd') ? fc_arg->last_buf : fc_arg->first_buf;
	while (value - i >= to && value - i >= 0)
	{
		tmp = ft_strlen(g_hist.hist[value - i]);
		if (tmp > 0 && g_hist.hist[value - i][tmp - 1] == '\n')
			tmp -= 1;
		ft_putnendl_fd(g_hist.hist[value - i], tmp, fd);
		i++;
	}
	return (0);
}

int					btin_fc_execute_edit(t_btin_fc *fc_arg,
						int flags, int fd, int flag)
{
	int				i;
	int				tmp;
	int				value;
	int				to;

	i = 0;
	value = (flag == 'd') ? fc_arg->first_buf : fc_arg->last_buf;
	to = (flag == 'd') ? fc_arg->last_buf : fc_arg->first_buf;
	while (value + i <= to && value + i < g_hist.len)
	{
		tmp = ft_strlen(g_hist.hist[value + i]);
		if (tmp > 0 && g_hist.hist[value + i][tmp - 1] == '\n')
			tmp -= 1;
		ft_putnendl_fd(g_hist.hist[value + i], tmp, fd);			
		i++;
	}
	return (0);
}