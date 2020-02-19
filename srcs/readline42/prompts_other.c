/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompts_other.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 11:40:02 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/19 15:37:02 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int				pipe_prompt(void)
{
	ft_putstr_fd("pipe> ", STDOUT_FILENO);
	g_rline.prompt_len = 6;
	return (0);
}

int				subshell_prompt(void)
{
	ft_putstr_fd("subshell> ", STDOUT_FILENO);
	g_rline.prompt_len = 10;
	return (0);
}

int				cursh_prompt(void)
{
	ft_putstr_fd("cursh> ", STDOUT_FILENO);
	g_rline.prompt_len = 10;
	return (0);
}

int				cmdandor_prompt(void)
{
	ft_putstr_fd("cmdandor> ", STDOUT_FILENO);
	g_rline.prompt_len = 10;
	return (0);
}
