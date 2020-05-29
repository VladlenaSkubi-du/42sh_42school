
#ifndef BUILTIN42_H
# define BUILTIN42_H

# include "fc.h"
# include "cd.h"

# define SUBOPTION_STARTS			16

typedef struct  s_ec
{
    int         e;
    int         n;
    int         up_e;
}               t_ec;

int				btin_exit(t_ltree *pos);
int				btin_exit_arguments(char **ar_v);

/*
** File usages.c
*/

int				usage_btin(char *str);
int				usage_btin_other(char *str);
int				usage_btin_fc(void);
int             usage_42sh(void);
int				ebash_long_options(void);

/*
** Folder fc, file fc.c
*/
int             btin_fc(t_ltree *pos);

/*
** Folder cd, file cd.c
*/

int				btin_cd(t_ltree *pos);

/*
** File init_structures.c
*/

t_btin_fc		*init_btin_fc(void);


/*
** File set.c
*/

int				btin_set(void);
int				btin_return_exit_status(void);

/*
** File unset.c
*/

int				btin_unset(t_ltree *pos);

/*
** File history.c
*/

int				btin_history(t_ltree *pos);
int				btin_history_clear(void);
int				btin_history_noargs(void);

/*
** File exsign_btin.c
*/

int				btin_exsign(t_ltree *pos);
int				btin_exsign_route_substitution(t_ltree *pos, int i);
int				btin_exsign_numeric(t_ltree *pos,
					int start, char *find);
int				btin_exsign_print_message(char *arg);
int				btin_exsign_make_substitution(t_ltree *pos,
					int start, char *subst);

/*
** File echo.c
*/

int             btin_echo(t_ltree *pos);

/*
** File pwd.c
*/

int             btin_pwd(t_ltree *pos);

/*
** File bg_fg_btin.c
*/

int				btin_bg(t_ltree *pos);
int				btin_fg(t_ltree *pos);

/*
** File jobs_btin.c
*/

int				btin_jobs(t_ltree *pos);

#endif
