/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashfunctionrealhash.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 16:23:46 by sschmele          #+#    #+#             */
/*   Updated: 2020/09/04 20:16:36 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

int				hashfunction_hash(char *cmd)
{
	int			index;

	index = ft_strlen(cmd);
	return (index);
}

int				collision_hashtable_find_hash(void **hashtable,
					int hashtable_size, int index, char *key)
{
	int			step;
	t_hashcmd	*slot_ptr;
	int			attempt;
	int			iterations;
	int			hash_key;

	ft_putendl_fd("hash collision find", STDOUT_FILENO);
	attempt = 1;
	slot_ptr = NULL;
	iterations = hashtable_size;
	hash_key = hashfunction_hash(key);
	while (!(slot_ptr && (slot_ptr->slot_state == 0 ||
			slot_ptr->slot_state == SLOT_DELETED_HASH)))
	{
		step = (hash_key + attempt * attempt) % hashtable_size;
		slot_ptr = (t_hashcmd*)hashtable[step];
		attempt++;
		iterations--;
		if (!iterations)
		{
			change_hashtable_filled_value(1);
			hashtable = get_hashtable_value(&hashtable_size);
			return (collision_hashtable_find_hash(hashtable,
				hashtable_size, hash_key, key));
		}
	}
	return (step);
}

int				collision_hashtable_add_hash(void **hashtable,
					int hashtable_size, char *key)
{
	int			index;

	index = 0;
	key = NULL;
	ft_putendl_fd("hash collision add", STDOUT_FILENO);
	return (index);
}
