/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 19:03:25 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/02 20:05:32 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

/*
** Ctrl: Ctrl-k, ctrl-t, ctrl-u (ctrl-w) is here (I take)
*/

int			ctrl_key(char sy, size_t pos)
{
	if (sy == '\013')
		write(STDERR_FILENO, "Ctrl-K\n", 8);
	else if (sy == '\024')
		write(STDERR_FILENO, "Ctrl-T\n", 8);
	else if (sy == '\025' || sy == '\027')
		write(STDERR_FILENO, "Ctrl-U(W)\n", 11);
	return (0);
}