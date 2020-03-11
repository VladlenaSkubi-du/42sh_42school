/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all42.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:05:06 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/11 14:08:43 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

int				clean_everything(void)
{
	ft_arrdel(g_env);
	ft_arrdel(g_rdovar);
	ft_arrdel(g_shvar);
	ft_arrdel(g_lovar);
	ft_arrdel(g_hist.hist);
	make_ctrl_y(2, NULL);
	clean_termcap();
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

int				clean_termcap(void)
{
	ft_bzero(g_cap.sf, TERMCAP_SIZE);
	ft_bzero(g_cap.le, TERMCAP_SIZE);
	ft_bzero(g_cap.nd, TERMCAP_SIZE);
	ft_bzero(g_cap.up, TERMCAP_SIZE);
	ft_bzero(g_cap.dow, TERMCAP_SIZE);
	ft_bzero(g_cap.cd, TERMCAP_SIZE);
	ft_bzero(g_cap.cr, TERMCAP_SIZE);
	return (0);
}