/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashfunctionrealhash.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 16:23:46 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/25 20:49:32 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

int				hashfunction_hash(char *cmd)
{
	cmd = NULL;
	ft_putendl_fd("normal hash function", STDOUT_FILENO);
	return (0);
}

int				collision_hashtable_find_hash(int index, char *key)
{
	index = 0;
	key = NULL;
	ft_putendl_fd("hash collision find", STDOUT_FILENO);
	return (0);
}

int				collision_hashtable_add_hash(char *key)
{
	int			index;

	index = 0;
	key = NULL;
	ft_putendl_fd("hash collision add", STDOUT_FILENO);
	return (index);
}
