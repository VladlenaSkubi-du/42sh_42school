/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_backend.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 16:26:38 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/24 16:09:58 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "hash.h"

int				hashtable_find(char *key, void **hashtable,
					int hashtable_size)
{
	int			index;
	t_hashcmd	*slot_ptr;

	index = 0;
	while (index < hashtable_size)
	{
		if (hashtable[index] != NULL)
		{
			slot_ptr = (t_hashcmd*)hashtable[index];
			if (ft_strcmp(key, slot_ptr->cmd_name) == 0 &&
					slot_ptr->slot_state == SLOT_FILLED_HASH)
				return (index);
		}
		index++;
	}
	return (HASHTABLE_NF);
}

char			*hashtable_add(char *key, void **hashtable,
					int hashtable_size, int *index)
{
	char		*path;
	int			i;
	int			hashtable_filled;

	path = path_search(key);
	if (!path)
		return (NULL);
	hashtable_filled = get_hashtable_filled();
	i = 0;
	while (i < hashtable_size)
	{
		if (hashtable[i] == NULL)
		{
			hashtable[i] = init_hash_cell(key, path);
			*index = i;
			return (path);
		}
		i++;
	}
	return (path);
}

int				hashtable_delete(char *key, void **hashtable,
					int hashtable_size, int hashtable_filled)
{
	int			index;

	if (hashtable_filled == 0)
		return (HASHTABLE_NF);
	index = hashtable_find(key, hashtable, hashtable_size);
	if (index == HASHTABLE_NF || hashtable[index] == NULL)
		return (HASHTABLE_NF);
	clear_hash_cell(index, hashtable, SLOT_FILLED_HASH);
	return (0);
}

int				hashtable_clean(void **hashtable,
					int hashtable_size)
{
	int				i;
	t_hashcmd		*hash_cell_ptr;
	int				hashtable_filled;

	i = 0;
	hashtable_filled = -1;
	hashtable_filled = get_hashtable_filled();
	if (hashtable_filled < 0)
		return (0);
	if (hashtable_filled == 0)
		return (0);
	while (i < hashtable_size)
	{
		if (hashtable[i] != NULL)
		{
			hash_cell_ptr = (t_hashcmd*)hashtable[i];
			clear_hash_cell(i, hashtable, 0);
		}
		i++;
	}
	change_hashtable_filled_value(0);
	return (0);
}

int				update_hashtable_slot_filled(t_hashcmd **slot_ptr)
{
	int			hashtable_filled;
	struct stat	stat_buf;

	hashtable_filled = -1;
	hashtable_filled = get_hashtable_filled();
	if (hashtable_filled < 0)
		return (0);
	change_hashtable_filled_value(1);
	(*slot_ptr)->slot_state = SLOT_FILLED_HASH;
	if (access((*slot_ptr)->cmd_path, X_OK) == -1 ||
			stat((*slot_ptr)->cmd_path, &stat_buf) != 0
			|| (stat_buf.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)) == 0 ||
			S_ISREG(stat_buf.st_mode) == 0)
		(*slot_ptr)->cmd_state = CDM_NON_EXEC;
	else
		(*slot_ptr)->cmd_state = 0;
	return (0);
}
