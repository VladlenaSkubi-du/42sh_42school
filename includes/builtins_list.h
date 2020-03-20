/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_list.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 19:07:24 by rbednar           #+#    #+#             */
/*   Updated: 2020/03/19 15:57:15 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_LIST_H
# define BUILTINS_LIST_H

# define BUILTINS_NUM 16

static char		*g_builtins[] = {"alias_fff", "unalias_fff", \
	"hash_fff", "set", "unset", "export_fff", \
	"cd", "exit", "echo_bi", "type_fff", "fg_ff", "bg_ff", "jobs_ff", "fc", \
	"history", NULL};

static int 		(*g_builtins_func[BUILTINS_NUM])() = {NULL, NULL, \
	NULL, btin_set, btin_unset, NULL, btin_cd, btin_exit, \
	NULL, NULL, NULL, NULL, NULL, btin_fc, btin_history, NULL};

#endif
