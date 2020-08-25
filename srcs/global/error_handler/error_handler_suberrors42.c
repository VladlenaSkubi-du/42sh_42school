/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler_suberrors42.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 16:43:43 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/25 22:26:34 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

/*
** Variable errors are errors that exit with 1
*/

int				variable_errors(int status, char *str)
{
	if ((status >> 9 & ERR_SET) || (status >> 9 & ERR_CD) ||
			(status >> 9 & ERR_ECHO))
	{
		ft_putendl_fd(str, STDERR_FILENO);
		return (0);
	}
	ft_putstr_fd(str, STDERR_FILENO);
	if (status >> 9 & ERR_RDONLY)
		ft_putendl_fd(": Readonly variable", STDERR_FILENO);
	else if (status >> 9 & ERR_HISTORY_NUM)
		ft_putendl_fd(": History specification out of range", STDERR_FILENO);
	else if ((status >> 9 & ERR_HISTORY_EXEC) ||
			(status >> 9 & ERR_HASH_NF))
		ft_putendl_fd(": No command found", STDERR_FILENO);
	else if (status >> 9 & ERR_UNSET)
		ft_putendl_fd(": Parameter null or not set", STDERR_FILENO);
	else if (status >> 9 & ERR_JOB_NF)
		ft_putendl_fd(": No such job", STDERR_FILENO);
	else if (status >> 9 & ERR_TOO_MANY)
		ft_putendl_fd(": Too many arguments", STDERR_FILENO);
	else if (status >> 9 & ERR_CD_NO_FILE_DIR)
		ft_putendl_fd(": No such file or directory found", STDERR_FILENO);
	else if (status >> 9 & ERR_CD_NO_DIR)
		ft_putendl_fd(": No such directory found", STDERR_FILENO);
	return (0);
}

/*
** Option errors are errors that exit with 2
*/

int				options_errors(int status, char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	if (status >> 9 & ERR_BTIN_INVALID)
		ft_putendl_fd(": Invalid option", STDERR_FILENO);
	else if (status >> 9 & ERR_BTIN_ARG)
		ft_putendl_fd(": Option requires an argument", STDERR_FILENO);
	return (0);
}

/*
** Syntax errors are errors that exit with 258
*/

int				syntax_errors(int status, char *str)
{
	if (status >> 9 & ERR_SQUOTE)
	{
		ft_putstr_fd("Unexpected EOF while looking for matching `",
			STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
		ft_putstr_fd(find_env_value("0"), STDERR_FILENO);
		ft_putstr_fd(": syntax error: ", STDERR_FILENO);
		ft_putendl_fd("Unexpected end of file", STDERR_FILENO);
		return (0);
	}
	if (status >> 9 & ERR_REDIR)
	{
		ft_putstr_fd("Syntax error near unexpected token `", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
		return (0);
	}
	ft_putstr_fd(str, STDERR_FILENO);
	if (status >> 9 & ERR_BAD_FD)
		ft_putendl_fd(": Bad file descriptor", STDERR_FILENO);
	if (status >> 9 & ERR_NUMERIC)
		ft_putendl_fd(": Numeric argument required", STDERR_FILENO);
	return (0);
}
