#include "shell42.h"
#include "builtin42.h"

/*char	*ft_cut_name(char *name)
{
	char    *tmp;
	int		i;

	i = ft_strlen(name) - 1;
	//printf("name = %s\n", name);
	while (name[i] && name[i] != '/')
		i--;
	i++;
	tmp = ft_strdup(name + i);
	//printf("tmp = %s\n", tmp);
	return (tmp);
}
*/
int		ft_error(char *name, int en)
{
    char	*tmp;
    char	*new_name;

	new_name = NULL;
	tmp = ft_strdup("cd: ");
	if (name) 
		tmp = ft_strrejoin(tmp, name);
	//ft_putstr_fd("cd", 2);
	if (en == 1)
		tmp = ft_strrejoin(tmp, ": string not in pwd");
	else if (en == 2)
		tmp = ft_strrejoin(tmp, ": no such file or directory");
	else if (en == 3)
		tmp = ft_strrejoin(tmp, ": permission denied");
	else if (en == 4)
		tmp = ft_strrejoin(tmp, ": not a directory");
	else if (en == 5)
		tmp = ft_strrejoin(tmp, "too many arguments");
	else if (en == 6)
		tmp = ft_strrejoin(tmp, "OLDPWD not set");
	else if (en == 7)
		tmp = ft_strrejoin(tmp, "HOME not set");
	error_handler(VARIABLE_ERROR | (ERR_CD << 9), tmp);
	free(tmp);
	free(new_name);
    return (1);
}

int         btin_cd(t_ltree *pos)
{
	int     i;
	t_cd    *flags;
	int		flags_check;

	flags_check = find_options(2, (char*[]){"LP", "--help"}, pos->ar_v);
	if (flags_check == 0x10000)
		return (usage_btin("cd"));
	if (flags_check < 0)
		return (btin_return_exit_status());
	flags = ft_xmalloc(sizeof(t_cd *));
	i = ft_cd_flags(pos->ar_v, flags);
	if (pos->ar_v[i] && pos->ar_v[i][0] == '-' &&
			i > 0 && ft_strcmp(pos->ar_v[i - 1], "--") == 0)
    {   
        error_handler(OPTIONS_REQUIRED | (ERR_BTIN_INVALID << 9), "cd");
        usage_btin("cd");
        return (1);
    }
	if (ft_valid_cd(pos->ar_v, i))
	{
		free(flags);
		return (1);
	}
	if (ft_cd_pars(pos->ar_v[i], g_envi, flags))
	{
		free(flags);
		return (1);
	}
	free(flags);
	return (0);
}
