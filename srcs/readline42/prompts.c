/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 12:45:21 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/28 18:06:37 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int				init_prompt(char flag)
{
	if (flag == 'm')
		g_prompt.prompt_func = main_prompt;
	else if (flag == 'd')
		g_prompt.prompt_func = dquote_prompt;
	else if (flag == 'h')
		g_prompt.prompt_func = heredoc_prompt;
	else if (flag == 's')
		g_prompt.prompt_func = subshell_prompt;
	g_prompt.prompt_func();
	return (0);
}

int				main_prompt(void)
{
	const char	*prompt = "42sh";

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

int				subshell_prompt(void)
{
	ft_putstr_fd("subsh> ", STDOUT_FILENO);
	g_rline.prompt_len = 7;
	return (0);
}
