/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 16:42:04 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/25 22:14:17 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

/*
** The list of the whole history buffer
** If HISTORY_LIMIT or 32767 is reached, numeration continues with 1
*/

int					btin_history(t_process *pos)
{
	int				flags;

	flags = find_options(2, (char*[]){"c", "--help"}, pos->argv);
	if (flags == HELP_FLAG)
		return (usage_btin("history"));
	if (flags < 0)
		return (BTIN_ERROR);
	if (pos->argc == 1 && !flags)
		return (btin_history_noargs());
	return (btin_history_check_options(pos->argv));
}

int					btin_history_error_message(char *option, int error)
{
	char			*error_message;

	error_message = ft_strjoin("history: ", option);
	if (error)
		error_handler(OPTIONS_REQUIRED |
			(ERR_BTIN_INVALID << 9), error_message);
	free(error_message);
	return (BTIN_ERROR);
}

int					btin_history_check_options(char **argv)
{
	int				i;

	i = 0;
	while (argv[++i])
	{
		if (argv[i][0] == '-')
		{
			if (!argv[i][1])
				return (btin_history_error_message(argv[i], OPTIONS_REQUIRED));
			else if (argv[i][1] == 'c')
				return ((check_posix_option(argv[i], "c",
					btin_history_error_message) != 0) ?
					BTIN_ERROR : btin_history_clear());
			else if (argv[i][1] == '-' && !argv[i][2])
				return (btin_history_noargs());
		}
		else
			return (btin_history_noargs());
	}
	return (0);
}

int					btin_history_noargs(void)
{
	int				i;
	int				num;
	int				tmp;

	i = 0;
	num = g_hist.last_fc - ((g_hist.last + 1 == g_hist.len) ?
		g_hist.len - 1 : g_hist.last) + 1;
	num += (num < 1) ? HISTORY_LIMIT : 0;
	while (g_hist.hist[i] && i < g_hist.len)
	{
		if (num > HISTORY_LIMIT)
			num = 1;
		tmp = ft_strlen(g_hist.hist[i]);
		if (tmp > 0 && g_hist.hist[i][tmp - 1] == '\n')
			tmp -= 1;
		ft_printf("%5d  %.*s\n", num, tmp, g_hist.hist[i]);
		num++;
		i++;
	}
	return (0);
}

int					btin_history_clear(void)
{
	int				li;
	int				co;
	int				size;

	ft_arrdel(g_hist.hist);
	g_hist.hist = NULL;
	li = find_in_variable(&co, "HISTSIZE");
	if (!ft_isdigit(g_envi[li][co]))
		size = MAX_HISTBUF;
	size = ft_atoi(g_envi[li] + co);
	if (size < 0 || size > HISTORY_LIMIT)
		size = MAX_HISTBUF;
	init_history_buffer(size);
	return (0);
}
