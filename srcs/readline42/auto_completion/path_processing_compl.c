/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_processing_compl.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:53:36 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/28 16:57:38 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

char				*find_path_compl(char *compl, int tmp)
{
	char			*path;
	size_t			i;
	size_t			j;

	if (g_rline.pos == 0)
		return (NULL);
	if (compl && compl[0] && tmp != -1)
	{
		i = g_rline.pos - 1;
		while (i > 0 && (ft_isalnum(g_rline.cmd[i]) ||
			g_rline.cmd[i] == '.' || g_rline.cmd[i] == '/'))
			i--;
		j = g_rline.pos - 1;
		while (j > 0 && (ft_isalnum(g_rline.cmd[j])
			|| g_rline.cmd[j] == '.'))
		{
			if (g_rline.cmd[j] == '/')
				break ;
			j--;
		}
		path = ft_strndup(g_rline.cmd + i + 1, j - i);
	}
	else
		path = ft_strdup("./");
	return (path);
}

char				*path_parse_compl(void)
{
	size_t			i;

	i = 0;
	while (g_env[i])
	{
		if (ft_strncmp(g_env[i], "PATH=", 5) == 0)
			return (g_env[i] + 5);
		i++;
	}
	return (NULL);
}
