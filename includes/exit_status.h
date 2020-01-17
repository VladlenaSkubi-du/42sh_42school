/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 16:51:28 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/17 16:08:27 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_STATUS_H
# define EXIT_STATUS_H

typedef enum        e_status
{
    SUCCESS,
    PARSER_ERROR, //единица для отслеживания неверного выхода из программы
    OPTIONS_REQUIRED = 2,
    MALLOC_ERROR = 12,
    TERMINAL_EXISTS = 111,
    TERMINAL_TO_NON,
    TERMINAL_TO_CAN,
    SYNTAX_ERROR = 258
}                   exit_status;

#endif