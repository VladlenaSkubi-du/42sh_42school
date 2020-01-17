#include "parser.h"

/*
** Envvironment variables as global?
*/

void	free_vec(char **vec)
{
	size_t	i;

	i = 0;
	while (vec[i])
	{
		free(vec[i])
		i++;
	}
	free(vec);
}

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

char	**path_parse(void)
{
	char	path_value;
	char	**ret;

	if (!(path_value = get_env("PATH"))
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
	DIR				path;

	ret = 0;
	path = opendir(env_path);
	while ((entity = readdir(path)))
	{
		if (!ft_strcmp(entity->d_name, name))
		{
			if (!(ret = (char *)malloc(ft_strlen(env_path) + ft_strlen(name) + 2))) /* You shoud use Vlada's awesome function */
			{
				free_vec(to_clean);
				return (0);
			}
			ret = form_path(ret, env_path, name);
			if (ret)
				break;
		}
	}
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
	DIR				path;
	struct dirent	*entity;

	if (!(path_array = path_parse()))
		return (0);
	to_clean = path_array;
	while(*path_array)
	{
		ret = locate_file(path_array);
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

	if (!ft_strchr(path, '/')) /* Builtin or $PATH case */
		ret = path_search(*exec_av);
	else /* Execution path case */
	{
		if (access(*exec_av, X_OK) == -1)
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
	if (!(path = path_init(exec_av)))
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
	free_vec(to_clean);
	return (0);
}
