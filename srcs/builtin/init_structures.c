/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 13:38:16 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/25 17:08:29 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

t_btin_fc			*init_btin_fc(void)
{
	t_btin_fc		*fc;

	fc = (t_btin_fc*)ft_xmalloc(sizeof(t_btin_fc));
	fc->flag = 0;
	fc->editor = NULL;
    fc->first = 0;
	fc->last = 0;
	fc->s_comp = NULL;
	fc->s_cmd = NULL;
	return (fc);
}

int					btin_return_exit_status(void)
{
	size_t			li;
	size_t			sy;
	
	li = find_in_variables(g_rdovar, &sy, "?");
	return (ft_atoi(&g_rdovar[li][sy]));
}