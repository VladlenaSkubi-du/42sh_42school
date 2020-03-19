
#include "shell42.h"
#include "builtin42.h"
/*
char        *ft_2nd_word(char *cmd, char ***env)
{
    int     i;
    int     len;
    char    *path;

    i = 0;
    while (cmd[i] && cmd[i] != ' ')
        i++;
    while (cmd[i] && cmd[i] == ' ')
        i++;
    len = i;
    while (cmd[len] && cmd[len] != ' ' && cmd[len] != '\t')
        len++;
    if (i == len)
        return (NULL);
    len -= i;
    path = ft_memalloc(len + 1);
    len = 0;
    while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\t')
        path[len++] = cmd[i++];
    path[len] = '\0';
    if (ft_strchr(path, '~') != NULL)
        ft_tild(&path, env);
    return (path);
}

static int  ft_valid_command(char *cmd)
{
    int     i;
    int     ct;

    i = 0;
    ct = 0;
    while (cmd[i])
    {
        while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
            i++;
        if (cmd[i] && cmd[i] != ' ' && cmd[i] != '\t')
            ct++;
        if (ct > 2)
        {
            ft_error(cmd, 1, NULL);
            return (0);
        }
        while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\t')
            i++;
    }
    return (1);
}

char        *ft_find_home(char **av)
{
    int     i;
    int     j;
    char    *path;

    i = 2;
    j = 0;
    path = NULL;
    while (av[i])
    {
        if (ft_strncmp(av[i], "HOME", 4) == 0)
            break ;
        i++;
    }
    if (av[i] == NULL)
        return (".");
    while (av[i][j] && av[i][j] != '=')
        j++;
    path = ft_strjoin(av[i] + j + 1, "");
    return (path);
}

void        ft_cd(char **av, char ***env, char *cmd)
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

void    ft_change_path(char **env, char *path)
{
    size_t  j;
    size_t  i;
    size_t  k;
    char    dir[999];

    chdir(path);
    getcwd(dir, 999);
    i = find_in_variables(env, &j, "OLDPWD");
    free(env[i]);
    k = find_in_variables(env, &j, "PWD");
    env[i] = ft_strjoin("OLDPWD=", env[k] + j); 
    //printf("%s, %s\n", env[i], env[k]);
    free(env[k]);
    //printf("%s\n", dir);
    env[k] = ft_strjoin("PWD=", dir);
}

static void ft_error(char *name, int en)
{
    ft_putstr_fd("cd", 2);
    if (en == 1)
        ft_putstr_fd(": string not in pwd: ", 2);
    if (en == 2)
        ft_putstr_fd(": no such file or directory: ", 2);
    if (en == 3)
        ft_putstr_fd(": permission dinaed: ", 2);
    if (en == 4)
        ft_putstr_fd(": not a directory: ", 2);
    if (en == 5)
        ft_putstr_fd(": too many arguments", 2);
    else
    {
        ft_putstr_fd(name, 2);
        ft_putchar_fd('\n', 2);
    }
}

void    ft_cd_env(char **env, char *name, int flag)
{
    size_t  j;
    size_t  i;

    if ((i = find_in_variables(env, &j, name)) == -1)
        return ;
    if (flag)
        ft_putendl(env[i] + j);
    ft_change_path(env, env[i] + j);
}

void    ft_cd_pars(char **argv, int i, char **env, t_cd *cd_flags)
{
    struct stat buff;

    if (argv[i][0] == '-' && ft_strlen(argv[i]) == 1)
        ft_cd_env(env, "OLDPWD", 1);
    else if (stat(argv[i], &buff) < 0)
        ft_error(argv[i], 2);
    else
        ft_change_path(env, argv[i]);
}

int         btin_cd(t_ltree *pos)
{
    size_t  i;
    t_cd    *cd_flags;

    //ft_putnbr(argc);
    if (pos->ar_c == 1)
        ft_cd_env(pos->envir, "HOME", 0);
    else
    {
        cd_flags = ft_xmalloc(sizeof(t_cd *));
        i = ft_cd_flags(pos->ar_v, cd_flags);
        ft_cd_pars(pos->ar_v, i, pos->envir, cd_flags);
        free(cd_flags);
    }
    //ft_putstr("FLAG");
    /*while (env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }*/
    return (0);
}
