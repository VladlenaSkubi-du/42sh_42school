/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 14:24:54 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/30 15:13:32 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

char		*copy_without_slash_enter(char *cmd, char *buf_cmd, size_t *cmd_len)
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
