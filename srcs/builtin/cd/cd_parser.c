#include <shell42.h>
#include <builtin42.h>

int		ft_o_dir(char *str)
{
	DIR		*dir;

	if (!(dir = opendir(str)))
		return (-1);
	closedir(dir);
	return (0);
}

char	*ft_cdpath(char *path)
{
	char	**arr;
	char	*res;
	int		i;
	int		j;

	if ((i = find_in_variable(&j, "CDPATH")) < 0 || !path)
		return (NULL);
	res = NULL;
	arr = ft_strsplit(g_envi[i] + j, ':');
	i = -1;
	while (arr[++i])
	{
		if (path[0] == '.' && path[1] == '.')
			continue ;
		//res = ft_strjoin(arr[i], "/");
		//res = ft_strrejoin(res, path);
		res = ft_new_path(path, arr[i]);
		if ((ft_o_dir(res)) == 0)
			break ;
		ft_strdel(&res);
	}
	ft_arrdel(arr);
	if (res != NULL)
	{
		ft_putendl(res);
		return (res);
	}
	return (NULL);
}

int		ft_cd_env(char *path, char **env, t_cd *flags)
{
	char	*name;
	int		i;
	int		j;

	name = path ? ft_strdup("OLDPWD") : ft_strdup("HOME");
	i = find_in_variable(&j, name);
	if (path && i < 0)
	{
		free(name);
		return ((ft_error(NULL, 6)));
	}
	free(name);
	if (path)
		ft_putendl(env[i] + j);
	name = ft_strdup(env[i] + j);
	return ((ft_change_path(name, env, flags)));
}

int		ft_cd_pars(char *path, char **env, t_cd *flags)
{
	struct stat buff;
	char		*tmp;

	if ((tmp = ft_cdpath(path)) != NULL)
		return (ft_change_path(tmp, env, flags));
	if (ft_strcmp(path, "-") == 0 || !path)
		return ((ft_cd_env(path, env, flags)));
	//if (stat(path, &buff) < 0)
	//{
	//    if (ft_check_cdpath(ft_strjoin("/", path), env))
	//        return (ft_error(path, 4));
	//}
	if (stat(path, &buff) < 0)
		return (ft_error(path, 2));
	else if (!S_ISDIR(buff.st_mode))
		return (ft_error(path, 4));
	else
		return (ft_change_path(ft_new_path(path, NULL), env, flags));
	return (0);
}
