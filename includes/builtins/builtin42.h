
#ifndef BUILTIN42_H
# define BUILTIN42_H

# include "fc.h"
# include "cd.h"
# include "hash.h"

# define SUBOPTION_STARTS			16

/*
** Flags masks used in @flags in btin_fc and btin_hash
*/

# define		FLAG_N 0x1
# define		FLAG_R 0x2
# define		FLAG_S 0x4
# define		FLAG_L 0x8
# define		FLAG_E 0x10

# define        ARG_ALIAS		-1
# define        ARG_BUILTIN		-2
# define		ARG_INVALID		-3

/*
** Structures
** ____________________________________________________________________________
*/

/*
** Structure for btin_echo
*/

typedef struct  s_ec
{
	int         e;
	int         n;
	int         up_e;
}               t_ec;

/*
** General functions for the builtin block
** ____________________________________________________________________________
*/

/*
** File usages.c
*/

int				usage_btin(char *str);
int				usage_btin_other(char *str);
int				usage_btin_fc(void);
int             usage_42sh(void);
int				ebash_long_options(void);

/*
** File init_structures.c
*/

t_btin_fc		*init_btin_fc(void);
int				btin_check_arg_if_cmd_name(char *arg);
int				check_if_builtin(char *cmd_name);
int				btin_return_exit_status(void);

/*
** Sigle-file builtins
** ____________________________________________________________________________
*/

/*
** File exit.c
*/

int				btin_exit(t_ltree *pos);
int				btin_exit_arguments(char **ar_v);

/*
** File set.c
*/

int				btin_set(void);

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
int				btin_exsign_start_substitution(t_ltree *pos, int i);
int				btin_exsign_route_substitution(t_ltree *pos,
					int start, int i);
int				btin_exsign_stop_signs(char tech);
int				btin_exsign_numeric(t_ltree *pos,
					int start, int end);
int				btin_exsign_print_message(char *arg, int end);
int				btin_exsign_make_substitution(t_ltree *pos,
					int start, int end, char *subst);

/*
** File echo.c
*/

int             btin_echo(t_ltree *pos);
void		    write_text(char **argv, int i, t_ec *echo_flags);
void		    write_e_echo(char **argv, int i);
void		    write_back_sl(char c);
int			    parse_echo_flags(char **argv, t_ec *echo_flags);

/*
** File pwd.c
*/

int             btin_pwd(t_ltree *pos);
int             btin_pwd_valid(char **argv);
int		        pwd_error(char c, int en);

/*
** File export.c
*/

int				btin_export(t_ltree *pos);
int			    export_p(void);
int			    export_add_vis(t_ltree *pos);
int			    do_vis(char *arg);
int			    change_or_add(char *arg);

/*
** File bg_fg_btin.c
*/

int				is_btin_only(job *j);
int				btin_bg(t_ltree *pos);
int				btin_fg(t_ltree *pos);

/*
** File bumblebee.c
*/

int		        btin_bumblebee(void);

/*
** Several-files builtins
** ____________________________________________________________________________
*/

/*
** Folder fc, file fc.c
*/

int             btin_fc(t_ltree *pos);

/*
** Folder cd, file cd.c
*/

int				btin_cd(t_ltree *pos);

/*
** Folder jobs_btin, file jobs_main_btin.c
*/

int				btin_jobs(t_ltree *pos);
int				print_job_info(job * j, int options);

/*
** Folder jobs_btin, file jobs_id_btin.c
*/

int				print_by_id(t_ltree *pos, int options);
int				id_check(t_ltree *pos);

/*
** Folder hash, file hash.c
*/

int             btin_hash(t_ltree *pos);
int				btin_hash_check_flags(char **argv);
int				btin_hash_error_message(char *option, int error);
int				btin_hash_clean_table();

int				btin_hash_list_hashtable(void);
int				btin_hash_delete_elements(char **argv);
int				btin_hash_add_to_hashtable(char **argv);
int				btin_hash_valid_argument_add(char *key);
int				btin_hash_valid_argument_delete(char *key);

#endif
