/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin42.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:45:45 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/14 20:24:44 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN42_H
# define BUILTIN42_H

# include "fc.h"

int				btin_exit(int status);


/*
** File usages.c
*/

int				usage_btin(char *str);
int				usage_btin_fc(void);

/*
** Folder fc, file fc.c
*/

int             btin_fc(int argc, char **argv, char **environ);

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

int                btin_history(void);

#endif
