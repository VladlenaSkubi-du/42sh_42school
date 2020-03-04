/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin42.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:45:45 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/04 19:41:45 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN42_H
# define BUILTIN42_H

typedef	struct	s_btin_fc
{
	char		*editor;
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
t_btin_fc		init_btin_fc(void);
int				btin_fc_check_options(char **argv, int *flags,
					t_btin_fc *fc_arg);
int				btin_fc_fill_structure(char **argv, int *flags,
					t_btin_fc **fc_arg);
int				btin_fc_l_args(char **argv, int i, t_btin_fc **fc_arg);


#endif
