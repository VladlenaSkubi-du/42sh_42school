/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_cmd_processing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 14:00:01 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/29 14:06:21 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

char			*init_buffer_cmd(size_t cmd_len, char *cmd, size_t *buf_len)
{
	char		*buf_cmd;
	
	buf_cmd = ft_xmalloc(cmd_len + 2);
	ft_strcpy(buf_cmd, cmd);
	buf_cmd[cmd_len] = '\n';
	buf_cmd[cmd_len + 1] = '\0';
	*buf_len = cmd_len + 1;
	return (buf_cmd);
}

char            *add_buffer_cmd(char *buf_cmd, size_t cmd_len,
                                    char *cmd, size_t *buf_len)
{
    buf_cmd = ft_realloc(buf_cmd, *buf_len, *buf_len,
			*buf_len + cmd_len + 1);
	ft_strcpy(buf_cmd + *buf_len, cmd);
	buf_cmd[*buf_len + cmd_len] = '\n';
	buf_cmd[*buf_len + cmd_len + 1] = '\0';
	*buf_len += cmd_len + 1;
    return (buf_cmd);
}