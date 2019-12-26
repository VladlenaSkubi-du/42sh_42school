#include "parser.h"

/*
** Envvironment variables as global?
*/



char	*get_env(char *var)
{
	char	*val;

	val = 0;
	if (!g_env)
		return (0);
	while (*g_env)
	{
		if (ft_strstr(*g_env, var))
			break;
		g_env++;
	}
	if (*g_env)
		val = ft_strdup(*g_env + ft_strlen(var) + 1);
	return (val);
}
	
int		path_search(char *name)
{

}

/*
** Here we should find check and return execpath
*/

}
char	*path_init(char **exec_av)
{
	char *ret;

	if (!ft_strchr(path, '/')) /* Builtin or $PATH case */
	{
		/* There was some weird idea about PATH content table. Now it is dead, lol */
	}
	else /* Execution path case */
	{
		if (access(exec_av, X_OK) == -1)
			return (0);
		ret = ft_strdup(exec_av[0]);
	}
	return (ret); /* ret could be NULL */
}

int	exec_core(char **exec_av)
{
	pid_t	child_pid;
	char	*path;
//	int		pipe[2];

//	pipe ? pipe(pipe) : 0;
	if (!(path = path_init(exec_av) == -1))
		return (-1);
	child_pid = fork();
	if (!child_pid)
	{
		/* ALSO check for builtins, pipes and redirections... Darn, that's a lot! */
//		using_pipe ? dup2(p[1], 1);
		if (execve(path, exec_av, g_env) == -1)
			exit(-1);
	}
	else if (child_pid < 0)
		return (-1);
	wait(&child_pid);
	free(path);
	free(exec_av);
}
