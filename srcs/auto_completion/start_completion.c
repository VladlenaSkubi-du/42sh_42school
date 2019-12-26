/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_completion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 15:27:02 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/26 15:38:12 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

/*
** @d = direction: binary-files ('b'), variables ('v'), arguments ('a')
*/

int             auto_completion(void)
{
    char        d;
    size_t      len;

    len = ft_strlen(g_rline.cmd);
    if (g_rline.pos == 0 && len == 0)
        d = 'b';
    
    return (0);
}