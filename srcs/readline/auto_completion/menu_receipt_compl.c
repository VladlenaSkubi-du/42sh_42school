#include "shell42.h"
#include "readline.h"

char				**get_variables(char *complete, int *total, int *max_len)
{
	char			**menu;
	t_path			*root;

	root = fill_tree_with_variables(complete, total);
	menu = ft_add_block(&root, (size_t)*total, max_len);
	ft_path_free(&root);
	return (menu);
}

t_path				*fill_tree_with_variables(char *complete, int *total)
{
	int				i;
	t_path			*root;
	char			*name;
	int 			len;

	i = 0;
	root = NULL;
	while (g_envi[i])
	{
		if (g_envi[i][0] && (g_envi[i][0] & SET_VIS))
		{
			len = ft_strlen(complete);
			name = ft_strndup(g_envi[i] + 1,
					ft_strchri(g_envi[i] + 1, '='));
			if (ft_strnequ(name, complete, len))
				insert(name, &root, (size_t*)total);
			free(name);
		}
		i++;
	}
	// while (g_env[i])
	// {
	// 	insert_variables_to_tree(g_env[i], complete, &root, total);
	// 	i++;
	// }
	// i = 0;
	// while (g_shvar[i])
	// {
	// 	insert_variables_to_tree(g_shvar[i], complete, &root, total);
	// 	i++;
	// }
	// i = 0;
	// while (g_lovar[i])
	// {
	// 	insert_variables_to_tree(g_lovar[i], complete, &root, total);
	// 	i++;
	// }
	return (root);
}

int					insert_variables_to_tree(char *array, char *complete,
						t_path **root, int *total) //to DELETE
{
	char			*tmp;
	int 			len;

	len = ft_strlen(complete);
	tmp = ft_strndup(array, ft_strchri(array, '='));
	if (ft_strnequ(tmp, complete, len))
		insert(tmp, root, (size_t*)total);
	free(tmp);
	return (0);
}

char				**get_arguments(char **complete,
						int *total, int *max_len)
{
	char			**menu;
	char			*path;
	char			*compl;
	int				tmp;
	t_path			*root;

	tmp = ft_strchri(*complete, '/');
	path = find_path_compl(*complete, tmp);
	compl = (tmp >= 0 && tmp < ft_strlen(*complete))
			? ft_strdup(*complete + tmp + 1) : NULL;
	if (compl != NULL)
	{
		free(*complete);
		*complete = compl;
	}
	root = fill_tree_with_arguments(path, *complete, total);
	if (root == NULL)
	{
		free(path);
		return (NULL);
	}
	menu = ft_add_block(&root, (size_t)*total, max_len);
	ft_path_free(&root);
	free(path);
	return (menu);
}

char				*find_path_compl(char *compl, int tmp)
{
	char			*path;
	int				i;
	int				j;

	if (g_rline.pos == 0)
		return (NULL);
	if (compl && compl[0] && tmp != -1)
	{
		i = g_rline.pos - 1;
		while (i > 0 && (ft_isalnum(g_rline.cmd[i]) || g_rline.cmd[i] == '.' ||
			g_rline.cmd[i] == '/' || g_rline.cmd[i] == '_'))
			i--;
		j = g_rline.pos - 1;
		while (j > 0 && (ft_isalnum(g_rline.cmd[j])
			|| g_rline.cmd[j] == '.'))
		{
			if (g_rline.cmd[j] == '/')
				break ;
			j--;
		}
		path = ft_strndup(g_rline.cmd + i + 1, j - i);
	}
	else
		path = ft_strdup("./");
	return (path);
}

t_path				*fill_tree_with_arguments(char *path,
						char *complete, int *total)
{
	t_path			*root;
	int				len;
	DIR				*dir_name;
	struct dirent	*entry;

	root = NULL;
	if (path == NULL)
		return (NULL);
	len = ft_strlen(complete);
	if (!(dir_name = opendir(path)))
		return (NULL);
	while ((entry = readdir(dir_name)))
	{
		if ((entry->d_name[0] == '.' && entry->d_name[1] == '\0') ||
			(entry->d_name[0] == '.' && entry->d_name[1] &&
			entry->d_name[1] == '.' && entry->d_name[2] == '\0') ||
			ft_isprint(entry->d_name[0]) == 0)
			continue ;
		if (ft_strnequ(entry->d_name, complete, len))
			insert(entry->d_name, &root, (size_t*)total);
	}
	closedir(dir_name);
	return (root);
}
