/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 14:24:54 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/30 18:46:31 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

char			*copy_without_slash_enter(char *cmd, char *buf_cmd, size_t *cmd_len)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (buf_cmd[i])
	{
		if ((buf_cmd[i] == '\\' && buf_cmd[i + 1] == '\n') || buf_cmd[i] == '\n')
			i++;
		else
		{
			cmd[j] = buf_cmd[i];
			i++;
			j++;
		}
	}
	cmd[j] = '\0';
	*cmd_len = j;
	return (cmd);
}

int				check_quotes(int *flag_quotes, t_stack **check)
{
	size_t		i;

	if (*flag_quotes == 0)
	{
		*check = ft_init_stack();
		*flag_quotes = 1;
	}
	i = 0;
	while (i < g_techline.len)
	{
		if (g_techline.line[i] == SQUOTE && (*check)->data != SQUOTE)
			ft_push_stack(check, SQUOTE);
		else if (g_techline.line[i] == SQUOTE && (*check)->data == SQUOTE)
			ft_pop_stack(check);
		if (g_techline.line[i] == DQUOTE && (*check)->data != DQUOTE)
			ft_push_stack(check, DQUOTE);
		else if (g_techline.line[i] == DQUOTE && (*check)->data == DQUOTE)
			ft_pop_stack(check);
		i++;
	}
	if ((*check)->data != 0)
		return (-1);
	return (0);
}
