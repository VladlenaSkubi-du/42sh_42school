/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_exec_mode_e.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 22:38:27 by vladlenasku       #+#    #+#             */
/*   Updated: 2020/03/26 23:13:04 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

int					btin_fc_execute_edition(t_btin_fc *fc_arg, int flags, char **envir)
{
	t_ltree			*sub;
	char			*tmpfile;
	int				fd;

	tmpfile = NULL;
	fd = ft_tmpfile_fc("tmp42sh_fc_XXXXXX", &tmpfile);
	if (fd < 0)
	{
		error_handler(TMPFILE, NULL);
		return (HIST_ERROR);
	}
	btin_fc_write_to_tmpfile(fc_arg, flags, fd);
	close(fd);
	sub = btin_fc_before_exec(fc_arg, envir, tmpfile);
	exec_init(sub); //still no errors
	//openfile and while it can be read, sent to parser
	free(sub);
	unlink(tmpfile);
	free(tmpfile);
	return (0);
}

t_ltree				*btin_fc_before_exec(t_btin_fc *fc_arg,
						char **envir, char *tmpfile)
{
	t_ltree			*sub;

	sub = (t_ltree *)ft_xmalloc(sizeof(t_ltree));
	ltree_init(sub);
	sub->envir = envir;
	sub->ar_v[0] = fc_arg->editor;
	sub->ar_v[1] = tmpfile;
	sub->ar_c = 2;
	return (sub);
}

int					btin_fc_write_to_tmpfile(t_btin_fc *fc_arg,
						int flags, int fd)
{
	if ((fc_arg->flag & ARG_FIRST) && !(fc_arg->flag & ARG_SECOND))
	{
		ft_putstr_fd(g_hist.hist[fc_arg->first_buf], fd);
		return (0);
	}
	if (flags & FLAG_R)
		btin_fc_execute_edit_reverse(fc_arg, flags, fd);
	else
		btin_fc_execute_edit(fc_arg, flags, fd);
	return (0);
}

int					btin_fc_execute_edit_reverse(t_btin_fc *fc_arg,
						int flags, int fd)
{
	int				i;
	int				tmp;
	
	i = fc_arg->last_buf;
	while (fc_arg->last_buf - i >= fc_arg->first_buf &&
		fc_arg->last_buf - i >= 0)
	{
		tmp = ft_strlen(g_hist.hist[fc_arg->last_buf - i]);
		if (tmp > 0 && g_hist.hist[fc_arg->last_buf - i][tmp - 1] == '\n')
			tmp -= 1;
		ft_putnstr_fd(g_hist.hist[fc_arg->last_buf - i], tmp, fd);
		i++;
	}
	return (0);
}

int					btin_fc_execute_edit(t_btin_fc *fc_arg,
						int flags, int fd)
{
	int				i;
	int				tmp;

	i = fc_arg->first_buf;
	while (fc_arg->first_buf + i <= fc_arg->last_buf &&
		fc_arg->first_buf + i < g_hist.len)
	{
		tmp = ft_strlen(g_hist.hist[fc_arg->first_buf + i]);
		if (tmp > 0 && g_hist.hist[fc_arg->first_buf + i][tmp - 1] == '\n')
			tmp -= 1;
		ft_putnstr_fd(g_hist.hist[fc_arg->first_buf + i], tmp, fd);			
		i++;
	}
	return (0);
}