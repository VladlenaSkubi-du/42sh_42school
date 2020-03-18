/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all42.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:05:06 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/18 13:53:59 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

/*
** Cleans all the arrays and structures that exist within the session
** These are all the shell variables, history (only in interactive mode)
** yank-key combination (only in interactive mode), termcap library (that
** is on stack but still, (only in interactive mode))
** If there is error in parser and it leaves with OUT, structure for
** command execution should still be cleaned
** (that is why we put ft_lst_ltree_clear)
*/

int				clean_everything(void)
{
	size_t		li;
	size_t		sy;
	
	li = find_in_variables(g_rdovar, &sy, "42SH_NONINTERACTIVE=");
	if (g_rdovar[li][sy] == '0')
	{
		ft_arrdel(g_hist.hist);
		ft_arrdel(g_shvar);
		make_ctrl_y(2, NULL);
		clean_termcap();
	}
	ft_arrdel(g_env);
	ft_arrdel(g_rdovar);
	ft_arrdel(g_lovar);
	// ft_lst_ltree_clear(&g_start_list); //TODO пересмотреть логику
	return (0);
}

/*
** Cleans the only structure that contains everything
** All the other cleanings are done within readline function
*/

int				clean_readline42(void)
{
	free(g_rline.cmd);
	return (0);
}

/*
** The main globals in parser
** @g_start_list is a list that comes to execution of commands
*/

int				clean_parser42(void)
{
	if (g_cmd)
		free(g_cmd);
	if (g_techline.line)
		free(g_techline.line);
	ft_lst_ltree_clear(&g_start_list);
	return (0);
}

/*
** Termcap is a libriry for treminal modification
** Is used only for the interactive mode
*/

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