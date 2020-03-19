/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin42.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:45:45 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/19 17:26:45 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN42_H
# define BUILTIN42_H

# include "fc.h"
# include "cd.h"

# define SUBOPTION_STARTS			16

int				btin_exit(int status);


/*
** File usages.c
*/

int				usage_btin(char *str);
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

/*
** File unset.c
*/

int				btin_unset(t_ltree *pos);

/*
** File history.c
*/

int				btin_history(void);

#endif
