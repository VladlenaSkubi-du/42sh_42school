/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_list.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 19:07:24 by rbednar           #+#    #+#             */
/*   Updated: 2020/03/12 22:05:02 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_LIST_H
# define BUILTINS_LIST_H

static char		*g_buildins[] = {"alias_fff", "unalias_fff", \
	"hash_fff", "set", "unset", "export_fff", \
	"cd_ff", "exit", "echo_bi" "type_fff", "fg_ff", "bg_ff", "jobs_ff", "fc_ff", NULL};

static int 		(*g_buildins_func[15])() = {NULL, NULL, \
	NULL, btin_set, btin_unset, NULL, NULL, btin_exit, \
	NULL, NULL, NULL, NULL, NULL, NULL, NULL};

#endif
