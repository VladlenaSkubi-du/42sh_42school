
#include "shell42.h"
#include "parser.h"
#include "builtins_list.h"

int		exec_old_init(t_ltree *pos)
{
	if (pos->ar_c < 1)
		return (0);
	return (exec_core_old(pos));
}

int		exec_core_old(t_ltree *pos)
{
	pid_t			child_pid;
	char			*path;
	static int		pipe_prev;
	static int		pipe_next[2];

	path = NULL;
	child_pid = 0;
	if (ft_builtins_check_old(pos, 0) == -1 && !(path = path_init(pos->ar_v)))
		return (exec_clean(path, -1, 0));
	(pos->flags & PIPED_IN) ? (pipe_prev = pipe_next[0]) : 0;
	if ((pos->flags & PIPED_OUT) && pipe(pipe_next) == -1)
		return (exec_clean(path, -1, "e-bash: Pipe failed")); //через error_handler
	fd_list_process(pos, 0);
	(pos->flags & PIPED_OUT) ? dup2(pipe_next[1], 1) : 0;
	(pos->flags & PIPED_IN) ? dup2(pipe_prev, 0) : 0;
	child_pid = 0;
	if (ft_builtins_check_old(pos, 1) == -1 &&
		fork_and_exec(pos, path, &child_pid) == -1)
		return (-1);
	(pos->flags & PIPED_OUT) ? close(pipe_next[1]) : 0;
	(pos->flags & PIPED_IN) ? close(pipe_prev) : 0;
	fd_list_process(pos, 1);
	return (exec_clean(path, WIFEXITED(child_pid) ? \
	WEXITSTATUS(child_pid) : (-1), 0));
}

int		ft_builtins_check_old(t_ltree *pos, int flag)
{
	int	i;

	i = 1;	
	while (g_builtins[i])
	{
		if (!ft_strcmp(pos->ar_v[0], g_builtins[i]))
		{
			if (flag)
				exit_status_variables(g_builtins_func[i](pos));
			return (i);
		}
		i++;
	}
	return (-1);
}