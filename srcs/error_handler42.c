/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler42.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:22:16 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/05 20:55:43 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

int				error_handler(int status, char *str)
{
	ft_putstr_fd("e-bash: ", STDERR_FILENO);
	if ((status & 0x1FF) & VARIABLE_ERROR)
		variable_errors(status, str);
	else if ((status & 0x1FF) & OPTIONS_REQUIRED)
		options_errors(status, str);
	else if ((status & 0x1FF) & TERMINAL_EXISTS)
		ft_putendl_fd("terminal does not exist, use -c flag", STDERR_FILENO); //TODO check
	else if ((status & 0x1FF) & TERMINAL_TO_NON)
		ft_putendl_fd("terminal can't be changed, use -c flag", STDERR_FILENO); //TODO check
	else if ((status & 0x1FF) & TERMINAL_TO_CAN)
		ft_putendl_fd("terminal can't be changed, reset the terminal",
			STDERR_FILENO); //TODO check
	else if ((status & 0x1FF) & SYNTAX_ERROR)
		syntax_errors(status, str);
	exit_status_variable(status);
	return (0);
}

int				variable_errors(int status, char *str)
{
	if (status >> 9 & ERR_RDONLY)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": readonly variable", STDERR_FILENO);
	}
	else if (status >> 9 & ERR_HISTORY)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": history specification out of range", STDERR_FILENO);
	}
	else if (status >> 9 & ERR_UNSET)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": parameter null or not set", STDERR_FILENO);
	}
	else if (status >> 9 & ERR_SET)
	{
		ft_putendl_fd(str, STDERR_FILENO);
	}
	return (0);
}

int				options_errors(int status, char *str)
{
	if (status >> 9 & ERR_EBASH_C)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": -c: option requires an argument", STDERR_FILENO);
	}
	else if (status >> 9 & ERR_BUILTIN)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": invalid option", STDERR_FILENO);
		usage_btin(str);
	}
	return (0);
}

int				syntax_errors(int status, char *str)
{
	if (status >> 9 & ERR_SQUOTE)
	{
		ft_putstr_fd("unexpected EOF while looking for matching `", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
		ft_putstr_fd("e-bash: ", STDERR_FILENO);
		ft_putstr_fd("syntax error: ", STDERR_FILENO);
		ft_putendl_fd("unexpected end of file", STDERR_FILENO);
	}
	if (status >> 9 & ERR_REDIR)
	{
		ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
	}
	syntax_errors_files(status, str);
	return (0);
}

int			syntax_errors_files(int status, char *str)
{
	if (status >> 9 & ERR_BAD_FD)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": Bad file descriptor", STDERR_FILENO);
	}
	if (status >> 9 & ERR_NO_ACC)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	}
	if (status >> 9 & ERR_NO_FILE)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	}
	return (0);
}
/*
** Errors possible in NON-INTERACTIVE MODE: 
** bash --posix -c "."
bash: line 0: .: filename argument required
.: usage: . filename [arguments]
echo $?
2


** bash --posix -c "/"
bash: /: is a directory
bash-3.2$ echo $?
126


** bash --posix -c "!"
bash: !: event not found
bash-3.2$ echo $?
0


** bash --posix -c "hallo"
bash: hallo: command not found
bash-3.2$ echo $?
127


** bash --posix -c "\""
bash: -c: line 0: unexpected EOF while looking for matching `"'
bash: -c: line 1: syntax error: unexpected end of file
bash-3.2$ echo $?
2


** bash --posix -c "{"
bash: -c: line 1: syntax error: unexpected end of file
bash-3.2$ echo $?
2


** bash --posix -c "; ; "
bash: -c: line 0: syntax error near unexpected token `;'
bash: -c: line 0: `; ; '
bash-3.2$ echo $?
2
*/

/*bash-3.2$ bash --posix -c "fg"
bash: line 0: fg: no job control
bash-3.2$ bash --posix -c "bg"
bash: line 0: bg: no job control
*/

/*
** Errors possible in INTERACTIVE MODE:
** 
*/
