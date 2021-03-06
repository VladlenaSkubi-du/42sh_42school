/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all42.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 16:44:46 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/21 21:18:36 by sschmele         ###   ########.fr       */
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
	if (ft_atoi(find_env_value("42SH_NONINTERACTIVE")) == 0)
	{
		if (g_hist.len >= 0)
			free(g_hist.hist[g_hist.len]);
		ft_arrdel(g_hist.hist);
		make_ctrl_p(2, NULL);
		btin_alias_init(NULL, NULL, DEL_ALL);
		btin_alias_init(NULL, NULL, CONTINUE);
		btin_hash_clean_table();
	}
	ft_arrdel(g_envi);
	cd_free_static();
	ft_gnl(GNL_CLEAN, NULL);
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
	if (g_prompt.prompt_func != heredoc_prompt)
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
