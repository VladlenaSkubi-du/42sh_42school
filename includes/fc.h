/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 17:29:20 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/12 19:26:47 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FC_H
# define FC_H

# define		POSIX_FC_DIFF 16

# define		HIST_ERROR -1
# define		HIST_EXEC 0
# define		HIST_SEARCH 1

# define		FLAG_N 0x2
# define		FLAG_R 0x4
# define		FLAG_S 0x8
# define		FLAG_L 0x10
# define		FLAG_E 0x20
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
int				btin_fc_save_editor(char **argv, int i, t_btin_fc **fc_arg);
int				btin_fc_one_int(int value);
int				btin_fc_two_ints(t_btin_fc **fc_arg);

/*
** File fc_modes_l.c
*/

int				btin_fc_list_mode(char **argv, int *flags,
					t_btin_fc **fc_arg);
int				btin_fc_list_mode_no_args(int *flags, t_btin_fc **fc_arg);
int				btin_fc_list_mode_num_args(char **argv, int i,
                    int *flags, t_btin_fc **fc_arg);
int				btin_fc_list_mode_flags_off(int *flags);

/*
** File fc_mode_s.c
*/

int				btin_fc_exec_mode(char **argv, int *flags,
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

/*
** File fc_exec.c
*/

int				btin_fc_route_execution(int flags, t_btin_fc *fc_arg);

#endif