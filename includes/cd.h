#ifndef CD_H
# define CD_H

typedef struct      s_cd
{
    size_t          p;
    size_t          l;
}                   t_cd;

int                 btin_cd(t_ltree *pos);
int                 ft_valid_cd(char **argv, int i);
int                 ft_error(char *name, int en);
int                 ft_check_cdpath(char *path, char **env);
#endif
