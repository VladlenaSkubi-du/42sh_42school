#include <shell42.h>
#include <builtin42.h>

int		ft_to_dir(char *path)
{
	if (chdir(path) == -1)
	{
		ft_error(path, 3);
		return (1);
	}
	change_oldpwd_value(get_pwd_value());
	return (0);
}

void		ft_change_pwd(char *path, char **env)
{
    int		i;
    int		j;
    int		c;
    //int		k;
	//char	c;
	char	*tmp;
    

	/*i = find_in_variable(&j, "OLDPWD");
	k = find_in_variable(&j, "PWD");
	c = env[i][0];
	free(env[i]);
	env[i] = ft_xmalloc(sizeof(char) * 9);
	env[i][0] = c;
	ft_strcpy(env[i] + 1, "OLDPWD=");
	env[i] = ft_strrejoin(env[i], env[k] + j);
	
	tmp = ft_strjoin("OLDPWD=", get_oldpwd_value());
	change_env_value(
	c = env[k][0];
	free(env[k]);
	env[k] = ft_xmalloc(sizeof(char) * 6);
	env[k][0] = c;
	ft_strcpy(env[k] + 1, "PWD=");
	env[k] = ft_strrejoin(env[k], path);
	//free(path);
	//printf("%s, %s\n", env[i] + 1, env[k] + 1);
	*/
	tmp = ft_strjoin("OLDPWD=", get_oldpwd_value());
	if ((i = find_in_any_variable(env, &j, "OLDPWD")) >= 0)
		change_env_value(tmp, (i = find_in_variable(&j, "OLDPWD")));
	else
	{
		c = add_new_env(tmp);
		g_envi[c][0] |= ENV_VIS;
	}
	free(tmp);
	tmp = ft_strjoin("PWD=", get_pwd_value());
	if ((i = find_in_any_variable(env, &j, "PWD")) >= 0)
		change_env_value(tmp, (i = find_in_variable(&j, "PWD")));
	else
	{
		c = add_new_env(tmp);
		g_envi[c][0] |= ENV_VIS;
	}
	free(tmp);
		
}

int		ft_change_path(char *path, char **env, t_cd *flags)
{
	//printf("%s\n", path);
	if (ft_to_dir(path))
	{
		free(path);
		return (1);
	}
	if (flags->p)
	{
		free(path);
		path = getcwd(NULL, MAXDIR);
	}
	change_pwd_value(path);
	/*if (flags->p)
		name = getcwd(NULL, 999);
	else
		name = path;
	*/ft_change_pwd(path, env);
	free(path);
	return (0);
}
