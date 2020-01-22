/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler42.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:22:16 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/22 19:36:27 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

int				error_handler(t_exit_status status, char *str)
{
	ft_putstr_fd("42sh: ", STDERR_FILENO);
	if (status == OPTIONS_REQUIRED)
		ft_putendl_fd("-c: option requires an argument", STDERR_FILENO);
	else if (status == TERMINAL_EXISTS)
		ft_putendl_fd("terminal does not exist, use -c flag", STDERR_FILENO); //TODO check
	else if (status == TERMINAL_TO_NON)
		ft_putendl_fd("terminal can't be changed, use -c flag", STDERR_FILENO); //TODO check
	else if (status == TERMINAL_TO_CAN)
		ft_putendl_fd("terminal can't be changed, reset the terminal",
			STDERR_FILENO); //TODO check
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
