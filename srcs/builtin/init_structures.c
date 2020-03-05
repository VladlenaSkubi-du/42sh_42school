/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 13:38:16 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/05 13:40:46 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

t_btin_fc			init_btin_fc(void)
{
	t_btin_fc		fc;

	fc.editor = NULL;
    fc.arg_e_first = -1;
	fc.arg_e_last = -1;
	fc.arg_l_first = -17;
	fc.arg_l_first = -1;
	fc.arg_s_comp = NULL;
	fc.arg_s_first = -1;
	return (fc);
}