/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 17:29:20 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/18 19:34:28 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FC_H
# define FC_H

# define		POSIX_FC_DIFF 16

# define		HIST_ERROR -2
# define		HIST_EXEC -1
# define		HIST_SEARCH 1

# define		FLAG_N 0x1
# define		FLAG_R 0x2
# define		FLAG_S 0x4
# define		FLAG_L 0x8
# define		FLAG_E 0x10
# define		ARG_FIRST 0x1
# define		ARG_SECOND 0x2
# define		ARG_SECOND 0x2
# define        FC_COMP_ARRAY 10

typedef	struct	s_btin_fc
{
	int			flag;
	char		*editor;
	int			first;
	int			last;
	int			first_buf;
	int			last_buf;
	char		**s_comp;
	char		*s_cmd;
}				t_btin_fc;

/*
** File fc.c
*/

int				btin_fc_find_mode(char **argv, int argc, int *flags,
					t_btin_fc **fc_arg);
int				btin_fc_save_editor(char **argv, int i,
					int j, t_btin_fc **fc_arg);

/*
** File fc_modes_l.c
*/

int				btin_fc_list_mode(char **argv, int j, int *flags,
					t_btin_fc **fc_arg);
int				btin_fc_list_mode_no_args(int *flags, t_btin_fc **fc_arg);
int				btin_fc_list_mode_num_args(char **argv, int i,
                    int *flags, t_btin_fc **fc_arg);
int				btin_fc_list_mode_flags_off(int *flags);

/*
** File fc_mode_s.c
*/

int				btin_fc_exec_mode(char **argv, int j, int *flags,
					t_btin_fc **fc_arg);

int				btin_fc_exec_mode_no_args(int *flags, t_btin_fc **fc_arg);
int				btin_fc_exec_mode_flags_off(int *flags);
int             btin_fc_exec_mode_proc(char **argv, int *flags,
					t_btin_fc **fc_arg);
int				btin_fc_exec_mode_add_comp(t_btin_fc **fc_arg, char *comp);

/*
** File fc_mode_e.c
*/

int				btin_fc_edit_mode(char **argv, int *flags,
					t_btin_fc **fc_arg);
int				btin_fc_edit_mode_num_args(char **argv, int i,
					int *flags, t_btin_fc **fc_arg);
int				btin_fc_edit_mode_flags_off(int *flags);

/*
** File fc_exec.c
*/

int				btin_fc_route_execution(int flags, t_btin_fc *fc_arg);

/*
** File fc_num_calc.c
*/

int				btin_fc_one_int__edit(int value);
int				btin_fc_two_ints__edit(t_btin_fc **fc_arg);
int				btin_fc_two_ints__list(t_btin_fc **fc_arg);
int				btin_fc_positive_int__list(int value,
					int from, int to, char flag);
int				btin_fc_calculate_nums__list(int buffer, int from);

#endif