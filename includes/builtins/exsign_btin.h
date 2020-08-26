/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exsign_btin.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 11:27:29 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/26 12:16:26 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXSIGN_BTIN_H
# define EXSIGN_BTIN_H

/*
** File exsign_btin.c
*/

int				btin_exsign_init(t_ltree *pos, int i);
int				btin_exsign_print_message(char *arg, int end);

/*
** File exsign_btin_processing.c
*/

int				btin_exsign_start_substitution(t_ltree *pos, int i);
int				btin_exsign_route_substitution(t_ltree *pos,
					int start, int i);
int				btin_exsign_stop_signs(char tech);
int				btin_exsign_numeric(t_ltree *pos,
					int start, int end);
int				btin_exsign_make_substitution(t_ltree *pos,
					int start, int end, char *subst);

#endif
