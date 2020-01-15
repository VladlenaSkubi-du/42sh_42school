/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 12:45:21 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/15 21:25:58 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int				init_prompt(char flag, char end, char *send)
{
	g_prompt.stop = (end) ? end : 0;
	g_prompt.sstop = (send) ? send : NULL;
	if (flag == 'm')
		g_prompt.prompt_func = main_prompt;
	else
		g_prompt.prompt_func = other_prompts;
	g_prompt.prompt_func(flag);
	return (0);
}

int				main_prompt(char flag)
{
	char		*prompt;

	prompt = "42sh";
	ft_putstr_fd("\033[1;31m", 1);
	ft_putstr_fd(prompt, 1);
	ft_putstr_fd("\033[0m", 1);
	ft_putstr_fd("> ", 1);
	g_rline.prompt_len = ft_strlen(prompt) + 2;
	return (0);
}

int				other_prompts(char flag)
{
	char		*prompt;

	if (flag == 'd')
		prompt = "dquote> ";
	else if (flag == 'h')
		prompt = "heredoc> ";
	else if (flag == 'c')
		prompt = "> ";
	ft_putstr_fd(prompt, 1);
	g_rline.prompt_len = ft_strlen(prompt) + 2;
	return (0);
}
