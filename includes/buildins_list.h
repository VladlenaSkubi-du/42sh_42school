/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_list.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 19:07:24 by rbednar           #+#    #+#             */
/*   Updated: 2020/03/12 19:09:12 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_LIST_H
# define BUILTINS_LIST_H

static char	*g_buildins[] = {"alias", "unalias", \
	"hash", "set", "unset", "export", \
	"cd", "exit", "echo", "type", "fg", "bg", "jobs", "fc", NULL};

static int (*g_buildins_func[15])() = {NULL, NULL, \
	NULL, btin_set, NULL, NULL, \
	NULL, btin_exit, NULL, NULL, NULL, NULL, NULL};

#endif
