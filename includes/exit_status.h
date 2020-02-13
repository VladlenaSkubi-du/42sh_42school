/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 16:51:28 by sschmele          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/02/13 18:30:55 by rbednar          ###   ########.fr       */
=======
/*   Updated: 2020/02/12 20:06:09 by sschmele         ###   ########.fr       */
>>>>>>> 10d7faf905343b17aef872e3e5a7b1ee2df9c34c
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_STATUS_H
# define EXIT_STATUS_H

# define	ERR_SQUOTE 0x1
# define	ERR_REDIR 0x2
# define	ERR_BAD_FD 0x4
# define	ERR_NO_ACC 0x8


/*
** In reality bash returns code "2" for all the internal errors + adds mask for
** explanation of general type error (main_error (=1) | general_mask >> 8) +
** adds explanation of local type error (main_error (=1) |
** general_mask >> 8 | local_mask >> 16)
**
** But we do the main_error_status + local_mask << 8
*/

enum				e_status
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
};

#endif
