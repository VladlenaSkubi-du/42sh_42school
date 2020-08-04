/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_list.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 19:07:24 by rbednar           #+#    #+#             */
/*   Updated: 2020/08/04 16:25:58 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_LIST_H
# define BUILTINS_LIST_H

# define BUILTINS_NUM 18

static char		*g_builtins[] = {"alias", "unalias", \
	"hash", "set", "unset", "export", \
	"cd", "exit", "echo", "type", "fg", "bg", "jobs", "fc", \
	"history", "pwd", "bumblebee", NULL};

static int 		(*g_builtins_func[BUILTINS_NUM])() = {btin_alias,\
	btin_unalias, btin_hash, btin_set, btin_unset, btin_export, btin_cd, btin_exit, \
	btin_echo, btin_type, btin_fg, btin_bg, btin_jobs, btin_fc, btin_history, \
	btin_pwd, btin_bumblebee, NULL};

#endif
