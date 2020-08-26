/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 16:08:09 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/26 12:15:44 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALIAS_H
# define ALIAS_H

/*
** File alias.c
*/

int				btin_alias_check_options(char **argv);
int				btin_alias_error_message(char *option, int error);
int				btin_alias_init(char **argv, char **ans, int flag);
int				btin_alias_print(t_list **alias, char **argv,
					char **ans, int flag);

/*
** File alias_copy.c
*/

int				btin_alias_copy_buf(t_list **alias, t_list **buf);

/*
** File alias_parse.c
*/

char			*find_in_alias(t_list **arr, char *name);
int				btin_alias_save(t_list **buf, char *arg, int eq);
int				btin_alias_print_one(char *arg);
int				btin_alias_merge_buf(t_list **arr, t_list *buf);
int				check_if_aliased(char *name);

/*
** File alias_help.c
*/

int				btin_alias_valid_name(char *name);
char			*btin_alias_line_form(char *arg);
int				btin_alias_check_name(t_list *arr, t_list *buf);
int				btin_alias_delete(t_list **alias, char *arg);
int				btin_alias_delete_all(t_list **alias);

#endif
