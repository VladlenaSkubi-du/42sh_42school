/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_start_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 18:13:02 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/28 18:54:56 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

int             quoting_to_readline(void)
{
    if (g_techline.line[g_techline.len - 1] == SLASH)
        printf("here\n");
    return (0);
}