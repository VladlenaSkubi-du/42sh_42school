/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all42.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:05:06 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/05 20:03:38 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

int				clean_everything(void)
{
	ft_arrdel(g_env);
	ft_arrdel(g_shvar);
	ft_arrdel(g_hist.hist);
    //другие clean
	make_ctrl_y(2, NULL);
	return (0);
}

int				clean_readline42(void)
{
	if (g_rline.cmd)
		free(g_rline.cmd);
	return (0);
}

int				clean_parser42(void)
{
	free(g_cmd);
	g_cmd = NULL;
	free(g_techline.line);
	g_techline.line = NULL;
	return (0);
}