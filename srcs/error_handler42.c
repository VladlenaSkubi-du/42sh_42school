/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler42.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:22:16 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/12 16:37:42 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

int				error_handler(t_exit_status status, char *str)
{
	ft_putstr_fd("e-bash: ", STDERR_FILENO);
	if ((status & 0xFFFF) == OPTIONS_REQUIRED)
		ft_putendl_fd("-c: option requires an argument", STDERR_FILENO);
	else if ((status & 0xFFFF) == TERMINAL_EXISTS)
		ft_putendl_fd("terminal does not exist, use -c flag", STDERR_FILENO); //TODO check
	else if ((status & 0xFFFF) == TERMINAL_TO_NON)
		ft_putendl_fd("terminal can't be changed, use -c flag", STDERR_FILENO); //TODO check
	else if ((status & 0xFFFF) == TERMINAL_TO_CAN)
		ft_putendl_fd("terminal can't be changed, reset the terminal",
			STDERR_FILENO); //TODO check
	else if ((status & 0x102) == SYNTAX_ERROR)
		syntax_errors(status, str);
	return (0);
}

int				syntax_errors(t_exit_status status, char *str)
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
	//изменение кода ошибки
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

/*
** Errors possible in INTERACTIVE MODE:
** 
*/
