#include "shell42.h"
#include "builtin42.h"

int					btin_fc_execute_execution(t_btin_fc *fc_arg, int flags)
{
	char			*cmd;
	int				i;

	if (fc_arg->s_cmd)
	{
		i = find_in_history(fc_arg->s_cmd);
		if (i == -1)
		{
			error_handler(VARIABLE_ERROR | (ERR_HISTORY_EXEC << 9), "fc");
			return (HIST_ERROR);
		}
		cmd = ft_strdup(g_hist.hist[i]);
		// printf("to find: %s - command found: %s\n", fc_arg->s_cmd, g_hist.hist[i]);
	}
	if (fc_arg->flag & ARG_FIRST)
	{
		cmd = ft_strdup(g_hist.hist[fc_arg->first_buf]);
		// printf("command number = %d, cmd = %s\n", fc_arg->first_buf, g_hist.hist[fc_arg->first_buf]);
	}
	if (fc_arg->s_comp)
	{
		cmd = make_history_assignments(fc_arg, cmd);
		// printf("command to launch: %s\n", cmd);
		btin_fc_exec_mode_add_comp(&fc_arg, NULL); //- добавить в exec
	}
	i = ft_strlen(cmd) - 1;
	cmd = (cmd[i] != '\n') ? ft_strrejoin(cmd, "\n") : cmd;
	parser(cmd);
	return (0);
}

char				*make_history_assignments(t_btin_fc *fc_arg, char *cmd)
{
	int				i;
	int				buf_len;
	char			*buf;
	int				eq;
	char			*what;

	buf_len = CMD_SIZE;
	buf = (char*)ft_xmalloc(buf_len + 1);
	eq = ft_strlen(cmd) - 1;
	(cmd[eq] == '\n') ? ft_strncpy(buf, cmd, eq) : ft_strcpy(buf, cmd);
	i = -1;
	while (fc_arg->s_comp[++i])
	{
		eq = ft_strchri(fc_arg->s_comp[i], '=');
		what = ft_strndup(fc_arg->s_comp[i], eq);
		if (ft_strstr(buf, what) == NULL)
		{
			free(what);
			continue ;
		}
		buf = insert_history_assignment(buf, buf_len,
			fc_arg->s_comp[i] + eq + 1, what);
	}
	free(cmd);
	return (buf);
}

char				*insert_history_assignment(char *buf, int buf_len,
						char *change, char *what)
{
	int				ptr;
	int				len_what;
	int				len_change;
	int				len_cmd;
	char			*tmp;

	tmp = ft_strstr(buf, what);
	ptr = tmp - buf;
	len_cmd = ft_strlen(buf);
	len_change = ft_strlen(change);
	len_what = ft_strlen(what);
	if (len_what == 0)
		return (insert_history_assignment_whole_line
			(buf, buf_len, change, len_change));
	tmp = ft_strdup(buf + ptr + len_what);
	if (len_cmd - len_what + len_change >= buf_len)
	{
		buf = ft_realloc(buf, len_cmd, buf_len, buf_len * 2);
		buf_len *= 2;
	}
	ft_strcpy(buf + ptr, change);
	ft_strcpy(buf + ptr + len_change, tmp);
	free(tmp);
	return (buf);
}

char				*insert_history_assignment_whole_line(char *buf, int buf_len,
						char *change, int len_change)
{
	int				i;
	int				len_cmd;
	int				len_full;
	int				ptr;

	i = -1;
	ptr = 0;
	len_cmd = ft_strlen(buf);
	len_full = len_cmd;
	while (++i < len_cmd)
	{
		if (len_full + len_change >= buf_len)
		{
			buf = ft_realloc(buf, len_cmd, buf_len, buf_len * 2);
			buf_len *= 2;
		}
		ft_strcpy(buf + ptr, change);
		ptr += len_change;
		len_full += len_change;
	}
	return (buf);
}