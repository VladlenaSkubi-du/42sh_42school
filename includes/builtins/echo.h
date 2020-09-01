/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 12:12:23 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/26 12:16:01 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ECHO_H
# define ECHO_H

/*
** Structure for btin_echo
*/

typedef struct	s_ec
{
	int			e;
	int			n;
	int			up_e;
}				t_ec;

/*
** File echo.c
*/

int				write_text(char **argv, int i, t_ec *echo_flags);
int				write_e_echo(char **argv, int i);
int				write_back_sl(char c);
int				parse_echo_flags(char **argv, t_ec *echo_flags, int i);

#endif
