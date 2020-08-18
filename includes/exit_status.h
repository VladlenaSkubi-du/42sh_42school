/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 16:51:28 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/18 20:01:23 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_STATUS_H
# define EXIT_STATUS_H

/*
** Variable errors are errors that exit with 1
** @ERR_JOB_NF is "job not found"
*/

# define	ERR_HISTORY_NUM 0x1
# define	ERR_HISTORY_EXEC 0x2
# define	ERR_RDONLY 0x4
# define	ERR_UNSET 0x8
# define	ERR_SET 0x10
# define	ERR_CD 0x20
# define	ERR_JOB_NF 0x40
# define	ERR_HASH_NF 0x80

/*
** Option errors are errors that exit with 2
*/

# define	ERR_BTIN_INVALID 0x1
# define	ERR_BTIN_ARG 0x2

/*
** Command errors for exit with 126 or 127
*/

# define	ERR_COMMAND 0x1
# define	ERR_ISDIR 0x2

/*
** Syntax errors are errors that exit with 258
*/

# define	ERR_SQUOTE 0x1
# define	ERR_REDIR 0x2
# define	ERR_BAD_FD 0x4
# define	ERR_NO_ACC 0x8
# define	ERR_NO_FILE 0x10
# define	ERR_NUMERIC 0x20

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
	VARIABLE_ERROR,
	OPTIONS_REQUIRED = 2,
	MALLOC_ERROR = 12,
	TERMINAL_EXISTS = 111,
	TERMINAL_TO_NON,
	TERMINAL_TO_CAN,
	TERMINAL_CHANGED,
	NONINERACTIVE,
	HISTORY_FILE_FAIL,
	TMPFILE,
	PIPE_FAILED,
	FORK_FAILED,
	SIGNAL_ERROR,
	COMMAND_NON_EXECUTABLE = 126,
	COMMAND_NOT_FOUND,
	SYNTAX_ERROR = 258
};

#endif
