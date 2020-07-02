#include <shell42.h>
#include <builtin42.h>

int		ft_to_dir(char *path)
{
	if (chdir(path) == -1)
	{
		ft_error(path, 3);
		return (1);
	}
	return (0);
}

void		ft_change_pwd(char *path, char **env)
{
    int		i;
    int		j;
    int		k;
	char	c;
    
	i = find_in_variable(&j, "OLDPWD");
	k = find_in_variable(&j, "PWD");
	c = env[i][0];
	free(env[i]);
	env[i] = ft_xmalloc(sizeof(char) * 9);
	env[i][0] = c;
	ft_strcpy(env[i] + 1, "OLDPWD=");
	env[i] = ft_strrejoin(env[i], env[k] + j);
	c = env[k][0];
	free(env[k]);
	env[k] = ft_xmalloc(sizeof(char) * 6);
	env[k][0] = c;
	ft_strcpy(env[k] + 1, "PWD=");
	env[k] = ft_strrejoin(env[k], path);
	//printf("%s, %s\n", env[i] + 1, env[k] + 1);
}

int		ft_change_path(char *path, char **env, t_cd *flags)
{
    char	*name;

	//printf("%s\n", path);
	if (ft_to_dir(path))
	{
		free(path);
		return (1);
	}
	if (flags->p)
		name = getcwd(NULL, 999);
	else
		name = path;
	ft_change_pwd(name, env);
	free(path);
	return (0);
}
