/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 12:45:21 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/24 13:31:50 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int				init_prompt(char flag, char *send)
{
	g_prompt.i = 0;
	g_prompt.sstop = (send) ? send : NULL;
	if (flag == 'm')
		g_prompt.prompt_func = main_prompt;
	else if (flag == 'd')
		g_prompt.prompt_func = dquote_prompt;
	else if (flag == 'h')
		g_prompt.prompt_func = heredoc_prompt;
	else
		g_prompt.prompt_func = other_prompt;
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

int				other_prompt(void)
{
	ft_putstr_fd("> ", STDOUT_FILENO);
	g_rline.prompt_len = 2;
	return (0);
}
