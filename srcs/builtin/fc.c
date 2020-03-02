/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 14:10:50 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/02 19:37:13 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

int                 btin_fc(int argc, char **argv, char **environ)
{
	int				tmp;
	
	tmp = find_options("erlns", argv, 1, "fc");
	return (0);
}
