/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 18:59:15 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/27 21:44:20 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int				main_prompt(void)
{
	char		*prompt;

	prompt = find_env_value("0");
	ft_putstr_fd("\033[1;31m", STDOUT_FILENO);
	ft_putstr_fd(prompt, STDOUT_FILENO);
	ft_putstr_fd("\033[0m", STDOUT_FILENO);
	ft_putstr_fd("> ", STDOUT_FILENO);
	g_prompt.prompt_len_real = ft_strlen(prompt) + 2;
	return (0);
}

int				dquote_prompt(void)
{
	const char	*prompt;

	prompt = "dquote> ";
	ft_putstr_fd(prompt, STDOUT_FILENO);
	g_prompt.prompt_len_real = ft_strlen(prompt);
	return (0);
}

int				heredoc_prompt(void)
{
	const char	*prompt;

	prompt = "heredoc> ";
	ft_putstr_fd(prompt, STDOUT_FILENO);
	g_prompt.prompt_len_real = ft_strlen(prompt);
	return (0);
}

int				other_prompt(void)
{
	const char	*prompt;

	prompt = "> ";
	ft_putstr_fd(prompt, STDOUT_FILENO);
	g_prompt.prompt_len_real = ft_strlen(prompt);
	return (0);
}

/*
** Here we count pos_x position for the first char in
** the line. It is done according to the prompt len and
** the width of the terminal: prompt len can be the same as
** the terminal width, longer and shorter
*/

int				count_prompt_len(void)
{
	if (g_screen.ws_col == 0)
		init_terminal_screen();
	if (g_prompt.prompt_len_real >= g_screen.ws_col)
		g_prompt.prompt_len = g_prompt.prompt_len_real %
			g_screen.ws_col;
	else
		g_prompt.prompt_len = g_prompt.prompt_len_real;
	if (g_prompt.prompt_len == 0)
	{
		putcap("sf");
		g_rline.flag |= NEW_LINE_SY;
		g_rline.flag |= PROMPTLEN_ZERO;
	}
	return (g_prompt.prompt_len);
}
