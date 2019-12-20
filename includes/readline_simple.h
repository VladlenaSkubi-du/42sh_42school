/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_simple.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 15:47:08 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/20 17:15:50 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_SIMPLE_H
# define READLINE_SIMPLE_H

# define SESC_NUM 4

/*
** File readline_simple.c
*/

char				*readline_simple(void);
int					sreadline_choice(char sy);
int					sescape_init(void);

/*
** File escape_simple.c
*/

int					sescape_check(char **seq_base);
int					ssequence_process(int sequence_num);
int					sesc_left(void);
int					sesc_right(void);

/*
** File help_functions.c
*/

int					bell_sound(void);

#endif