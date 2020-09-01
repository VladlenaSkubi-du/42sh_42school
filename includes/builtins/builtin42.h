/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin42.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 16:08:34 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/26 23:10:23 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN42_H
# define BUILTIN42_H

# include "fc.h"
# include "cd.h"
# include "hash.h"
# include "alias.h"
# include "export.h"
# include "exsign_btin.h"
# include "bg_fg_btins.h"
# include "echo.h"
# include "jobs_btin.h"

# define SUBOPTION_STARTS 16

/*
** Flags masks used in @flags in btin_fc and btin_hash
*/

# define FLAG_N 0x10
# define FLAG_R 0x20
# define FLAG_S 0x40
# define FLAG_L 0x80
# define FLAG_E 0x100
# define FLAG_P 0x200

# define ARG_ALIAS -10
# define ARG_BUILTIN -20
# define ARG_INVALID -30

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
int				usage_42sh(void);
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
int				btin_exit_args(char **ar_v);
int				btin_exit_error(char *option, int error);

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
int				btin_unset_error_message(char *find);

/*
** File history.c
*/

int				btin_history(t_process *pos);
int				btin_history_check_options(char **argv);
int				btin_history_error_message(char *option, int error);
int				btin_history_clear(void);
int				btin_history_noargs(void);

/*
** File pwd.c
*/

int				btin_pwd(t_process *pos);
int				btin_pwd_init(char **argv);
int				btin_pwd_valid(char **argv);
int				btin_pwd_error_message(char *option, int error);

/*
** File bumblebee.c
*/

int				btin_bumblebee(void);

/*
** File unalias.c
*/

int				btin_unalias(t_process *pos);
int				btin_unalias_check_options(char **argv);
int				btin_unalias_error(char *option, int error);
int				btin_unalias_init(char **argv);
int				btin_unalias_clean_commands(void);

/*
** File echo.c. Continuation in echo.h
*/

int				btin_echo(t_process *pos);

/*
** Several-files builtins
** ____________________________________________________________________________
*/

/*
** Folder alias, file alias.c. Continuation in alias.h
*/

int				btin_alias(t_process *pos);

/*
** Folder jobs_btin, file jobs_main_btin.c. Continuation in jobs_btin.h
*/

int				btin_jobs(t_process *pos);

/*
** Folder bg_fg_btins, file bg.c. Continuation in bg_fg_btins.h
*/

int				btin_bg(t_process *pos);

/*
** Folder bg_fg_btins, file fg.c. Continuation in bg_fg_btins.h
*/

int				btin_fg(t_process *pos);

/*
** Folder hash, file hash.c. Continuation in hash.h
*/

int				btin_hash(t_process *pos);

/*
** Folder exsign_btin, file exsign_btin.c. Continuation in exsign_btin.h
*/

int				btin_exsign(t_ltree *pos);

/*
** Folder export, file export.c. Continuation in export.h
*/

int				btin_export(t_process *pos);

/*
** Folder fc, file fc.c. Continuation in fc.h
*/

int				btin_fc(t_process *pos);

/*
** Folder cd, file cd.c. Continuation in cd.h
*/

int				btin_cd(t_process *pos);

#endif
