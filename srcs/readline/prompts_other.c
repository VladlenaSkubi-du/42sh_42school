/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompts_other.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 18:59:39 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/21 17:30:59 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int				pipe_prompt(void)
{
	const char	*prompt;

	prompt = "pipe> ";
	ft_putstr_fd(prompt, STDOUT_FILENO);
	g_prompt.prompt_len_real = ft_strlen(prompt);
	return (0);
}

int				cmdandor_prompt(void)
{
	const char	*prompt;

	prompt = "cmdandor> ";
	ft_putstr_fd(prompt, STDOUT_FILENO);
	g_prompt.prompt_len_real = ft_strlen(prompt);
	return (0);
}
