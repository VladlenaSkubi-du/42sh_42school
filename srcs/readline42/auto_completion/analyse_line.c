/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 18:24:47 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/18 17:19:03 by sschmele         ###   ########.fr       */
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

int			analyse_techline_compl(char *tech_line, size_t len, int *pool)
{
    size_t	i;

	i = len - 1;
	while (i > 0)
	{
		
	}
    return (0);
}