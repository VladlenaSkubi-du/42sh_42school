
#include "shell42.h"
#include "builtin42.h"
/*void        ft_cd(char **av, char ***env, char *cmd)
{
    struct stat buff;
    char        *path;

    if (!ft_valid_command(cmd))
        return ;
    path = ft_2nd_word(cmd, env);
    if (!path || (ft_strlen(path) == 1 && !ft_strncmp(path, "~", 1)))
    {
        chdir(path = ft_find_home(av));
        ft_change_path(env);
    }
    else if (!ft_strncmp(path, "-", 1) && ft_strlen(path) == 1)
        ft_cd_past(env);
    else if (stat(path, &buff) < 0)
        ft_error(cmd, 2, env);
    else if (!S_ISDIR(buff.st_mode))
        ft_error(cmd, 4, env);
    else if (chdir(path) == -1)
        ft_error(cmd, 3, env);
    else
        ft_change_path(env);
    if (path)
        free(path);
}
*/

size_t  ft_cd_flags(char **argv, t_cd *cd_flags)
{
    size_t  i;

    i = 1;
    while (argv[i] && argv[i][0] == '-')
    {
        if (ft_strlen(argv[i]) != 2 || (argv[i][1] != 'P' && argv[i][1] != 'L'))
            return (i);
        if (argv[i][1] == 'P')
            cd_flags->p = 1;
        else if (argv[i][1] == 'L')
            cd_flags->l = 1;
        i++;
    }
    return (i);
}

int  ft_error(char *name, int en)
{
    char    *tmp;

    tmp = ft_strdup("cd: ");
    if (name)
        tmp = ft_strrejoin(tmp, name);
    //ft_putstr_fd("cd", 2);
    if (en == 1)
        tmp = ft_strrejoin(tmp, ": string not in pwd");
    else if (en == 2)
        tmp = ft_strrejoin(tmp, ": no such file or directory");
    else if (en == 3)
        tmp = ft_strrejoin(tmp, ": permission dinaed");
    else if (en == 4)
        tmp = ft_strrejoin(tmp, ": not a directory");
    else if (en == 5)
        tmp = ft_strrejoin(tmp, "too many arguments");
    error_handler(VARIABLE_ERROR | (ERR_CD << 9), tmp);
    free(tmp);
    return (1);
}

int     ft_change_path(char **env, char *path)
{
    size_t  j;
    size_t  i;
    size_t  k;
    char    dir[999];

    if (chdir(path) == -1)
    {
        ft_error(path, 3);
        return (1);
    }
    getcwd(dir, 999);
    i = find_in_variables(env, &j, "OLDPWD");
    free(env[i]);
    k = find_in_variables(env, &j, "PWD");
    env[i] = ft_strjoin("OLDPWD=", env[k] + j); 
    free(env[k]);
    //printf("%s\n", dir);
    env[k] = ft_strjoin("PWD=", dir);
    //printf("%s, %s\n", env[i], env[k]);
    return (0);
}

int     ft_cd_env(char **env, char *name, int flag)
{
    size_t  j;
    size_t  i;

    if ((i = find_in_variables(env, &j, name)) == -1)
        return (0);
    if (flag)
        ft_putendl(env[i] + j);
    return (ft_change_path(env, env[i] + j));
}

int     ft_cd_pars(char **argv, int i, char **env, t_cd *cd_flags)
{
    struct stat buff;

    if (!argv[i])
        ft_cd_env(env, "HOME", 0);
    else if (argv[i][0] == '-' && ft_strlen(argv[i]) == 1)
        ft_cd_env(env, "OLDPWD", 1);
    else if (stat(argv[i], &buff) < 0)
    {
        if (ft_check_cdpath(ft_strjoin("/", argv[i]), env))
            return (ft_error(argv[i], 2));
    }
    else if (!S_ISDIR(buff.st_mode))
        return (ft_error(argv[i], 4));
    else
        return (ft_change_path(env, argv[i]));
    return (0);
}

int     btin_cd(t_ltree *pos)
{
    size_t  i;
    t_cd    *cd_flags;

    cd_flags = ft_xmalloc(sizeof(t_cd *));
    i = ft_cd_flags(pos->ar_v, cd_flags);
    if (ft_valid_cd(pos->ar_v, i))
    {
        free(cd_flags);
        return (1);
    }
    if (ft_cd_pars(pos->ar_v, i, g_env, cd_flags))
    {
        free(cd_flags);
        return (1);
    }
    free(cd_flags);
    return (0);
}
