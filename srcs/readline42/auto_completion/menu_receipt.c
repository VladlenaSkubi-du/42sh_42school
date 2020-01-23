/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_receipt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:17:28 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/23 17:58:07 by sschmele         ###   ########.fr       */
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
	size_t		i;
	t_path		*root;
	char		*tmp;
	size_t		len;

	i = 0;
	len = ft_strlen(complete);
	root = NULL;
	while (g_env[i])
	{
		tmp = ft_strndup(g_env[i], ft_strchri(g_env[i], '='));
		if (ft_strnequ(tmp, complete, len))
			insert(tmp, &root, total);
		free(tmp);
		i++;
	}
	i = 0;
	while (g_shvar[i])
	{
		tmp = ft_strndup(g_shvar[i], ft_strchri(g_shvar[i], '='));
		if (ft_strnequ(tmp, complete, len))
			insert(tmp, &root, total);
		free(tmp);
		i++;
	}
	menu = ft_add_block(&root, *total, max_len);
	ft_path_free(&root);
	return (menu);
}

char			**get_arguments(char *complete, size_t *total, int *max_len)
{
	char		**menu = NULL;

	printf("arguments\n");
	return (menu);
}
