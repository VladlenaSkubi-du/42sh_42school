#include "shell42.h"
#include "parser.h"

void	free_vec(char **vec)
{
	size_t	i;

	i = 0;
	while (vec[i])
	{
		free(vec[i]);
		i++;
	}
	free(vec);
}

char	*get_env(char *var)
{
	char	*val;
	size_t	i;

	val = 0;
	i = 0;
	if (!g_env)
		return (0);
	while (g_env[i])
	{
		if (ft_strstr(g_env[i], var))
			break;
		i++;
	}
	if (g_env[i])
		val = ft_strdup(g_env[i] + ft_strlen(var) + 1);
	return (val);
}

char	**path_parse(void)
{
	char	*path_value;
	char	**ret;

	if (!(path_value = get_env("PATH")))
		return (0);
	ret = ft_strsplit(path_value, ':');
	free(path_value);
	return (ret);
}

char	*form_path(char *ret, char *env_path, char *name)
{
	ft_bzero(ret, ft_strlen(env_path) + ft_strlen(name) + 2);
	ft_strcpy(ret, env_path);
	ft_strcat(ret, "/");
	ft_strcat(ret, name);
	if (access(ret, X_OK) == -1)
	{
		free(ret);
		ret = 0;
	}
	return (ret);
}

char	*locate_file(char *env_path, char *name, char **to_clean)
{
	struct dirent	*entity;
	char			*ret;
	DIR				*path;

	ret = 0;
	path = opendir(env_path);
	if (path == NULL)
		return (NULL);
	while ((entity = readdir(path)))
	{
		if (!ft_strcmp(entity->d_name, name))
		{
			if (!(ret = (char *)malloc(ft_strlen(env_path) + ft_strlen(name) + 2))) /* You shoud use Vlada's awesome function */
			{
				free_vec(to_clean);
				closedir(path);
				return (0);
			}
			ret = form_path(ret, env_path, name);
			if (ret)
				break;
		}
	}
	closedir(path);
	return (ret);
}

/*
** This is "just executable name case". We should check all directories in $PATH, find first match
** and check its accessibility
*/

char	*path_search(char *name)
{
	char			**path_array;
	char			**to_clean;
	char			*ret;

	if (!(path_array = path_parse()))
		return (0);
	to_clean = path_array;
	while(*path_array)
	{
		ret = locate_file(*path_array, name, to_clean);
		if (ret)
			break;
		path_array++;
	}
	free_vec(to_clean);
	return (ret);  /* Returns zero if we did not find anything */
}

/*
** Here we should find check and return execpath
*/

char	*path_init(char **exec_av)
{
	char *ret;

	if (!ft_strchr(*exec_av, '/')) /* Builtin or $PATH case */
		ret = path_search(*exec_av);
	else /* Execution path case */
	{
		if (access(*exec_av, X_OK) == -1)
			return (0);
		ret = ft_strdup(exec_av[0]);
	}
	return (ret); /* ret could be NULL */
}

/*
** So, let's talk about pipes:
** 1) If only PIPED_OUT -- create pipe
** 2) If only PIPED_IN -- delete pipe
*/

/*
** consider changing architecture to... well, something else
*/

int	exec_clean(char **exec_av, char *path, int exit_status)
{
	free(path);
	free_vec(exec_av);
	return (exit_status);
}

int	exec_core(char **exec_av, int flags)
{
	pid_t			child_pid;
	char			*path;
	static int		pipe_prev;
	static int		pipe_next[2];

	if (!(path = path_init(exec_av)))
		return (exec_clean(exec_av, path, -1));
	(flags & PIPED_IN) && (pipe_prev = pipe_next[0]);
	if ((flags & PIPED_OUT) && pipe(pipe_next) == -1)
			return (exec_clean(exec_av, path, -1));
	child_pid = fork();
	if (!child_pid)
	{
		(flags & PIPED_OUT) && dup2(pipe_next[1], 1);
		(flags & PIPED_IN) && dup2(pipe_prev, 0);
		if (execve(path, exec_av, g_env) == -1)
			exit(-1);
	}
	else if (child_pid < 0)
		return (exec_clean(exec_av, path, -1));
	wait(&child_pid);
	(flags & PIPED_OUT) && close(pipe_next[1]);
	(flags & PIPED_IN) && close(pipe_prev);
	return (exec_clean(exec_av, path, WIFEXITED(child_pid) ? 
		WEXITSTATUS(childpid : (-1))));
}
