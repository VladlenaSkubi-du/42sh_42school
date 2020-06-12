/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_list.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 19:07:24 by rbednar           #+#    #+#             */
/*   Updated: 2020/06/12 16:30:21 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_LIST_H
# define BUILTINS_LIST_H

# define BUILTINS_NUM 18

static char		*g_builtins[] = {"alias_fff", "unalias_fff", \
	"hash_fff", "set", "unset", "export_fff", \
	"cd", "exit", "echo", "type_fff", "fg", "bg", "jobs", "fc", \
	"history", "pwd", "bumblebee", NULL};

static int 		(*g_builtins_func[BUILTINS_NUM])() = {NULL,
	NULL, NULL, btin_set, btin_unset, NULL, btin_cd, btin_exit,
	btin_echo, NULL, btin_fg, btin_bg, btin_jobs, btin_fc, btin_history,
	btin_pwd, btin_bumblebee, NULL};

#endif
