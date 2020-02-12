/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 16:51:28 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/12 18:59:41 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_STATUS_H
# define EXIT_STATUS_H

# define	ERR_SQUOTE 0x1
# define	ERR_REDIR 0x2

/*
** In reality bash returns code "2" for all the internal errors + adds mask for
** explanation of general type error (main_error (=1) | general_mask >> 8) +
** adds explanation of local type error (main_error (=1) |
** general_mask >> 8 | local_mask >> 16)
**
** But we do the main_error_status + local_mask << 8
*/

typedef enum		e_status
{
	SUCCESS,
	PARSER_ERROR, //единица для отслеживания неверного выхода из программы
	OPTIONS_REQUIRED = 2,
	MALLOC_ERROR = 12,
	TERMINAL_EXISTS = 111,
	TERMINAL_TO_NON,
	TERMINAL_TO_CAN,
	HISTORY_FILE_FAIL,
	COMMAND_NOT_FOUND = 127,
	SYNTAX_ERROR = 258
}					t_exit_status;

#endif
