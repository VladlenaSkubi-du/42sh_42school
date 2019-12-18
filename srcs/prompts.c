/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 12:45:21 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/18 13:02:18 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int		main_promt(void)
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

int		other_prompts(char flag)
{
	char		*prompt;
	
	if (flag == 'd')
		prompt = "dquote> ";
	else if (flag == 'h')
		prompt = "heredoc> ";
	else if (flag == 'c')
		prompt = "> ";
	g_rline.prompt_len = ft_strlen(prompt) + 2;
	return (0);
}
