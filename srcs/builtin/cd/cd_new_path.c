#include <shell42.h>
#include <builtin42.h>

void	ft_del_prev(char **arr, int i)
{
	while (i > 0)
	{
		if (ft_strcmp(arr[i], ".") && ft_strcmp(arr[i], ".."))
		{
			free(arr[i]);
			arr[i] = ft_strdup(".");
			break ;
		}
		i--;
	}
}

void	ft_del_dots(char **arr)
{
    int		i;

	i = 0;
	while (arr[i])
	{
		if (ft_strcmp(arr[i], "..") == 0)
			ft_del_prev(arr, i);
		i++;
	}
}

char	*ft_new_from_arr(char **arr)
{
    int		i;
    char	*tmp;

	i = 0;
	tmp = ft_memalloc(1);
	ft_del_dots(arr);
	while (arr[i])
	{
	//	printf("%s\n", arr[i]);
		if (ft_strcmp(arr[i], ".") && ft_strcmp(arr[i], ".."))
		{
			if (i > 1)
				tmp = ft_strrejoin(tmp, "/");
			tmp = ft_strrejoin(tmp, arr[i]);
		}
		i++;
	}
	//printf("%d\n", i);
	return (tmp);
}

char	*ft_join(char *path, char **env)
{
	int		i;
	int		j;
	char	*tmp;

	//i = find_in_variable(&j, "PWD"); //Если его нет?
	//printf("%s\n", g_envi[22]);
	tmp = ft_strdup("1");
	tmp = ft_strrejoin(tmp, get_pwd_value());//env[i] + j);
	tmp = ft_strrejoin(tmp, "/");
//	tmp = ft_strjoin(env[i] + j, "/");
	tmp = ft_strrejoin(tmp, path);
	return (tmp);
}

char	*ft_new_path(char *path, char **env)
{
	char	*new_path;
	char	*tmp;
	char	**arr;

	//добавить проверку на абсолютный путь
	if (path[0] == '/')
		return (tmp = ft_strdup(path));
	tmp = ft_join(path, env);
	arr = ft_strsplit(tmp, '/');
	free(arr[0]);
	arr[0] = ft_strdup("/");
		//printf("%s\n", arr[0]);
	free(tmp);
	new_path = ft_new_from_arr(arr);
	//printf("RES = %s\n", new_path);
	ft_arrdel(arr);
	return (new_path);
}

