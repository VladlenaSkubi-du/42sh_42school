/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 11:25:48 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/26 12:16:17 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H

/*
** File export.c
*/

int				export_p(void);
int				export_add_vis(char **argv);
int				do_vis(char *arg);
int				change_or_add(char *arg);

/*
** File export_helper.c
*/

int				export_error(char **tmp, int i);

#endif
