/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_from_type.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 13:21:10 by a18589270         #+#    #+#             */
/*   Updated: 2020/08/21 16:14:42 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "hash.h"

/*
** Returns NULL or full path to a key (command)
** returns NULL is command is not found in hashtable and after
** PATH parsing
** returns path is the command is hashed (where changes to 1)
** or if command is not hashed but found in PATH parsing - only
** if it is executable (where is changed to 0)
*/

char		*hashtable_type_init(int *where, char *key)
{
	void		**hashtable;
	int			hashtable_size;
	int			index;
	t_hashcmd	*slot_ptr;

	hashtable_size = -1;
	hashtable = get_hashtable_value(&hashtable_size);
	if (hashtable_size < 0)
		return (NULL);
	index = hashtable_find(key, hashtable, hashtable_size);
	if (index == HASHTABLE_NF)
		return (hash_key_not_found_type(where, key));
	slot_ptr = (t_hashcmd*)hashtable[index];
	if (access(slot_ptr->cmd_path, F_OK) == -1 ||
			access(slot_ptr->cmd_path, X_OK) == -1)
	{
		clear_hash_cell(index, hashtable, 0);
		return (hash_key_not_found_type(where, key));
	}
	*where = 1;
	return (ft_strdup(slot_ptr->cmd_path));
}

char		*hash_key_not_found_type(int *where, char *key)
{
	char		*path;

	path = NULL;
	path = path_search(key);
	*where = 0;
	return ((path == NULL) ? NULL : path);
}
