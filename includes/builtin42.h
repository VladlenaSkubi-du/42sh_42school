/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin42.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:45:45 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/11 18:38:50 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN42_H
# define BUILTIN42_H

# define		POSIX_FC_DIFF 16

typedef	struct	s_btin_fc
{
	int			flag;
	char		*editor;
	int			first;
	int			last;
	int			first_buf;
	int			last_buf;
	char		*s_comp;
	char		*s_cmd;
}				t_btin_fc;

int				btin_exit(int status);


/*
** File usages.c
*/

int				usage_btin(char *str);
int				usage_btin_fc(void);

/*
** FIle fc.c
*/

int             btin_fc(int argc, char **argv, char **environ);
int				btin_fc_find_mode(char **argv, int argc, int *flags,
					t_btin_fc **fc_arg);
int				btin_fc_edit_mode(char **argv, int *flags,
					t_btin_fc **fc_arg);
int				btin_fc_list_mode(char **argv, int *flags,
					t_btin_fc **fc_arg);
int				btin_fc_exec_mode(char **argv, int *flags,
					t_btin_fc **fc_arg);
int				btin_fc_save_editor(char **argv, int i, t_btin_fc **fc_arg);
int				btin_fc_route_execution(int flags, t_btin_fc *fc_arg);
int				btin_fc_one_int(int value);
int				btin_fc_two_ints(t_btin_fc **fc_arg);

/*
** File init_structures.c
*/

t_btin_fc		*init_btin_fc(void);

#endif
