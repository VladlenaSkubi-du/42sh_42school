/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_chars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 20:29:13 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/13 15:54:14 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		swap_chars(char *cmd, int b, int a)
{
	char	tmp;

	tmp = cmd[b];
	cmd[b] = cmd[a];
	cmd[a] = tmp;
}
