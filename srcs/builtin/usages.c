/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usages.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 13:52:18 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/03 14:02:24 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

int             usage_btin(char *str)
{
    ft_putstr_fd(str, STDERR_FILENO);
    ft_putstr_fd(": usage: ", STDERR_FILENO);
    if (ft_strcmp(str, "fc") == 0)  
        usage_btin_fc();
    return (0);
}

int             usage_btin_fc(void)
{
    ft_putstr_fd("fc [-e editor] [-nlr] [first] [last]", STDERR_FILENO);
    ft_putendl_fd(" or fc -s [pat=rep] [cmd]", STDERR_FILENO);
    return (0);
}