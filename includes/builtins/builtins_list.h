/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_list.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 19:07:24 by rbednar           #+#    #+#             */
/*   Updated: 2020/03/30 19:46:39 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_LIST_H
# define BUILTINS_LIST_H

# define BUILTINS_NUM 17

static char		*g_builtins[] = {"alias_fff", "unalias_fff", \
	"hash_fff", "set", "unset", "export_fff", \
	"cd", "exit", "echo", "type_fff", "fg", "bg", "jobs", "fc", \
	"history", "pwd", NULL};

static int 		(*g_builtins_func[BUILTINS_NUM])() = {NULL,\
	NULL, NULL, btin_set, btin_unset, NULL, btin_cd, btin_exit, \
	btin_echo, NULL, btin_fg, btin_bg, btin_jobs, btin_fc, btin_history, btin_pwd, NULL};

#endif
