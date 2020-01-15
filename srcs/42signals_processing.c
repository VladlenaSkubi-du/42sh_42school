/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42signals_processing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:43:36 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/15 21:29:23 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

int             signals_reroute(void)
{
	signal(SIGTTOU, signal_handler);
	return(0);
}

static void		sig_tstp(int sig)
{
	
}

void            signal_handler(int sig)
{
	if (sig == SIGTTOU)
		sig_tstp(sig);
}