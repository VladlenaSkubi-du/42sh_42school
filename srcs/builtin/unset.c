/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 18:16:37 by kfalia-f          #+#    #+#             */
/*   Updated: 2020/08/24 13:44:01 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

int		btin_unset_error_message(char *find)
{
	char	*error;

	error = ft_strjoin("unset: ", find);
	error_handler(VARIABLE_ERROR | (ERR_RDONLY << 9), error);
	free(error);
	free(find);
	find = NULL;
	return (BTIN_ERROR);
}

int		btin_unset_init(int argc, char **argv)
{
	int		i;
	int		tmp;
	int		j;
	char	*find;

	i = 0;
	while (++i < argc)
	{
		if ((tmp = ft_strchri(argv[i], '=')) >= 0)
			find = ft_strndup(argv[i], tmp);
		else
			find = ft_strdup(argv[i]);
		if ((j = find_in_variable(&tmp, find)) < 0)
		{
			free(find);
			continue ;
		}
		if (g_envi[j][0] && (g_envi[j][0] & READONLY))
			return (btin_unset_error_message(find));
		else
			ft_arrshift(g_envi + j + 1, g_var_size - j, -1);
		free(find);
	}
	return (0);
}

int		btin_unset(t_process *pos)
{
	int		flags;

	flags = find_options(2, (char*[]){"", "--help"}, pos->argv);
	if (flags == HELP_FLAG)
		return (usage_btin("unset"));
	if (flags < 0)
		return (btin_return_exit_status());
	return (btin_unset_init(pos->argc, pos->argv));
}
