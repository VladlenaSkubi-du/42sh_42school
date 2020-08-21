/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exsign_btin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 16:27:40 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/21 20:36:21 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

/*
** Builtin !: !! is the last history-cmd in the buffer
** !word is the last history-cmd that starts with word
** !number is the history-cmd according to the number
** !-number is the history-cmd of the same number if count from
** the last cmd
*/

int					btin_exsign(t_ltree *pos)
{
	int				i;
	int				len_arg;
	char			**arg_tline;
	char			*line_part;

	argv_forming(pos);
	arg_tline = ft_strsplit(pos->l_tline.line, SPACE);
	i = 0;
	while (i < pos->ar_c)
	{
		len_arg = ft_strlen(pos->ar_v[i]);
		if (check_kind_assign(i, len_arg, arg_tline))
			break ;
		i++;
	}
	ft_arrdel(arg_tline);
	line_part = ft_strstr(pos->l_cmd, pos->ar_v[i]);
	ft_arrdel(pos->ar_v);
	pos->ar_v = NULL;
	i = line_part - pos->l_cmd - 1;
	return (btin_exsign_init(pos, i));
}

int					btin_exsign_init(t_ltree *pos, int i)
{
	while (++i < (int)pos->l_tline.len &&
			!btin_exsign_stop_signs(pos->l_tline.line[i]))
	{
		if (pos->l_tline.line[i] == BANG &&
				(pos->l_tline.line[i + 1] == BANG ||
				pos->l_tline.line[i + 1] == WORD_P ||
				pos->l_tline.line[i + 1] == TEXT))
			return (btin_exsign_start_substitution(pos, i));
		else if (pos->l_tline.line[i] == BANG)
		{
			pos->err_i = i + 1;
			pos->flags |= (ERR_OUT | ERR_R | ERR_REDIR << 16);
			return (ERR_OUT | ERR_R);
		}
	}
	return (0);
}

int					btin_exsign_print_message(char *arg, int end)
{
	ft_putstr_fd(find_env_value("0"), STDOUT_FILENO);
	ft_putstr_fd(": ", STDOUT_FILENO);
	ft_putnstr_fd(arg, end, STDOUT_FILENO);
	ft_putendl_fd(": event not found", STDOUT_FILENO);
	return (ERR_OUT);
}
