/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin42.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:45:45 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/05 20:28:22 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN42_H
# define BUILTIN42_H

typedef	struct	s_btin_fc
{
	char		*editor;
	int			arg_e_first;
	int			arg_e_last;
	int			arg_l_first;
	int			arg_l_last;
	char		*arg_s_comp;
	int			arg_s_first;
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
int				btin_fc_fill_structure(char **argv, int *flags,
					t_btin_fc **fc_arg);
int				btin_fc_no_args(char **argv, t_btin_fc **fc_arg, int flags);
int				btin_fc_e_args(char **argv, int j, t_btin_fc **fc_arg);
int				btin_fc_l_args(char **argv, int j, t_btin_fc **fc_arg);
int				btin_fc_s_args(char **argv, int j, t_btin_fc **fc_arg);

/*
** File init_structures.c
*/

t_btin_fc		*init_btin_fc(void);

#endif
