/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 12:45:21 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/30 17:55:12 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int				main_prompt(void)
{
	const char	*prompt = "e-bash";

	ft_putstr_fd("\033[1;31m", STDOUT_FILENO);
	ft_putstr_fd(prompt, STDOUT_FILENO);
	ft_putstr_fd("\033[0m", STDOUT_FILENO);
	ft_putstr_fd("> ", STDOUT_FILENO);
	g_rline.prompt_len = ft_strlen(prompt) + 2;
	return (0);
}

int				dquote_prompt(void)
{
	ft_putstr_fd("dquote> ", STDOUT_FILENO);
	g_rline.prompt_len = 8;
	return (0);
}

int				heredoc_prompt(void)
{
	ft_putstr_fd("heredoc> ", STDOUT_FILENO);
	g_rline.prompt_len = 9;
	return (0);
}

int				other_prompt(void)
{
	ft_putstr_fd("> ", STDOUT_FILENO);
	g_rline.prompt_len = 2;
	return (0);
}