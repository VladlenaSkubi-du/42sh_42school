
#ifndef BUILTIN42_H
# define BUILTIN42_H

# include "fc.h"
# include "cd.h"
# include "hash.h"

# define SUBOPTION_STARTS			16

/*
** Flags masks used in @flags in btin_fc and btin_hash
*/

# define		FLAG_N 0x10
# define		FLAG_R 0x20
# define		FLAG_S 0x40
# define		FLAG_L 0x80
# define		FLAG_E 0x100
# define		FLAG_P 0x200

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
int				check_posix_option(char *arg, char *options,
					int (f)(char *arg, int error));

/*
** Sigle-file builtins
** ____________________________________________________________________________
*/

/*
** File exit.c
*/

int				btin_exit(t_process *pos);
int				btin_exit_arguments(char **ar_v);

/*
** File set.c
*/

int				btin_set(t_process *pos);
int				btin_set_init(void);

/*
** File type.c
*/

int				btin_type(t_process *pos);
int				btin_type_check_options(char **argv);
int				btin_type_error_message(char *option, int error);
int				btin_type_init(char **argv);
int				btin_type_turn_to_hash(char *arg);

/*
** File unset.c
*/

int				btin_unset(t_process *pos);
int				btin_unset_init(int argc, char **argv);
void			btin_unset_error_message(char *find);

/*
** File history.c
*/

int				btin_history(t_process *pos);
int				btin_history_check_options(char **argv);
int				btin_history_error_message(char *option, int error);
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

int             btin_echo(t_process *pos);
void		    write_text(char **argv, int i, t_ec *echo_flags);
void		    write_e_echo(char **argv, int i);
void		    write_back_sl(char c);
int			    parse_echo_flags(char **argv, t_ec *echo_flags, int i);

/*
** File pwd.c
*/

int             btin_pwd(t_process *pos);
int				btin_pwd_init(char **argv);
int             btin_pwd_valid(char **argv);
int				btin_pwd_error_message(char *option, int error);

/*
** File export.c
*/

int				export_error(char **tmp, int i);
int				btin_export(t_process *pos);
int			    export_p(void);
int			    export_add_vis(char **argv);
int			    do_vis(char *arg);
int			    change_or_add(char *arg);

/*
** File bumblebee.c
*/

int		        btin_bumblebee(void);

/*
** File unalias.c
*/

int				btin_unalias(t_process *pos);
int				btin_unalias_check_options(char **argv);
int				btin_unalias_error(char *option, int error);
int				btin_unalias_init(char **argv);
int				btin_unalias_clean_commands(void);

/*
** Several-files builtins
** ____________________________________________________________________________
*/

/*
** Folder alias, file alias.c
*/

int				btin_alias(t_process *pos);
int				btin_alias_check_options(char **argv);
int				btin_alias_error_message(char *option, int error);
int				btin_alias_init(char **argv, char **ans, int flag);
int				btin_alias_print(t_list **alias, char **argv,
					char **ans, int flag);

/*
** Folder alias, file alias_copy.c
*/

int				btin_alias_copy_buf(t_list **alias, t_list **buf);

/*
** Folder alias, file alias_parse.c
*/

char			*find_in_alias(t_list **arr, char *name);
int				btin_alias_save(t_list **buf, char *arg, int eq);
int				btin_alias_print_one(char *arg);
int				btin_alias_merge_buf(t_list **arr, t_list *buf);
int				check_if_aliased(char *name);

/*
** Folder alias, file alias_help.c
*/

int				btin_alias_valid_name(char *name);
char			*btin_alias_line_form(char *arg);
int				btin_alias_check_name(t_list *arr, t_list *buf);
int				btin_alias_delete(t_list **alias, char *arg);
int				btin_alias_delete_all(t_list **alias);

/*
** Folder fc, file fc.c
*/

int             btin_fc(t_process *pos);

/*
** Folder cd, file cd.c
*/

int				btin_cd(t_process *pos);

/*
** Folder jobs_btin, file jobs_main_btin.c
*/

int				btin_jobs(t_process *pos);
int				btin_jobs_init(int argc, char **argv);
int				print_job_info(t_job * j, int options);
int				get_status(t_job	*j, char *buff, int options);

/*
** Folder jobs_btin, file jobs_id_btin.c
*/

int				print_by_id(int argc, char **argv, int options);
int				id_check(int argc, char **argv);

/*
** Folder jobs_btin, file jobs_btin_processing.c
*/

int				btin_jobs_check_options(char **argv, int *iter);
int				btin_jobs_error_message(char *option, int error);

/*
** Folder bg_fg_btins, file bg.c
*/

int				btin_bg(t_process *pos);
int				btin_bg_check_options(int argc, char **argv);

/*
** Folder bg_fg_btins, file fg.c
*/

int				btin_fg(t_process *pos);
int				btin_fg_check_options(int argc, char **argv);

/*
** Folder bg_fg_btins, file bg_fg_processing.c
*/

int				is_btin_only(t_job *j);
int				back_to_life(t_job *j);
int				btin_bg_init(int argc, char **argv);
int				btin_fg_init(int argc, char **argv);
int				btin_bg_fg_error_message(int where, char *option, int error);

/*
** Folder hash, file hash.c
*/

int             btin_hash(t_process *pos);
int				btin_hash_check_options(char **argv);
int				btin_hash_check_flags(char *arg);
int				btin_hash_error_message(char *option, int error);
int				btin_hash_clean_table();

int				btin_hash_list_hashtable(void);
int				btin_hash_delete_elements(char **argv);
int				btin_hash_add_to_hashtable(char **argv);
int				btin_hash_valid_argument_add(char *key);
int				btin_hash_valid_argument_delete(char *key);

#endif
