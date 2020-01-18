/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 18:24:47 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/17 18:35:40 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

char        *get_techline_compl(char *complete, size_t len)
{
    char    *tech_line;
    size_t  i;
    
    tech_line = (char*)ft_xmalloc(len);
    i = 0;
    while (g_rline.cmd[i] && i < len)
    {
        tech_line[i] = get_tech_num(g_rline.cmd[i]);
        i++;
    }
    return (tech_line);
}