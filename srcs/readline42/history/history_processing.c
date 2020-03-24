/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_processing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:18:29 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/24 00:40:19 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int		delete_last_history_element(void)
{
	free(g_hist.hist[g_hist.last]);
	g_hist.hist[g_hist.last] = NULL;
	g_hist.counter--;
	g_hist.last--;
	if (g_hist.last_fc < 1)
	   g_hist.last_fc =  g_hist.len - 1;
	return (0);
}