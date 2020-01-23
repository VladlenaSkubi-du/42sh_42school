/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_receipt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:17:28 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/23 16:34:16 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

char			*path_parse_compl(void)
{
	size_t		i;

	i = 0;
	while (g_env[i])
	{
		if (ft_strncmp(g_env[i], "PATH=", 5) == 0)
			return (g_env[i] + 5);
		i++;
	}
	return (NULL);
}

char			**get_variables(char *complete, size_t *total, int *max_len)
{
	char		**menu = NULL;

	printf("variables\n");
	return (menu);
}

char			**get_arguments(char *complete, size_t *total, int *max_len)
{
	char		**menu = NULL;

	printf("arguments\n");
	return (menu);
}
