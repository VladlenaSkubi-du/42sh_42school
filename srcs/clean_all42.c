/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all42.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:05:06 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/02 19:01:32 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

int				clean_everything(void)
{
	ft_arrdel(g_env);
	ft_arrdel(g_shvar);
	ft_arrdel(g_lovar);
	ft_arrdel(g_hist.hist);
    //другие clean
	make_ctrl_y(2, NULL);
	return (0);
}

int				clean_readline42(void)
{
	free(g_rline.cmd);
	return (0);
}

int				clean_parser42(void)
{
	if (g_cmd)
		free(g_cmd);
	if (g_techline.line)
		free(g_techline.line);
	return (0);
}