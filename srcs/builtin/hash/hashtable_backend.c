#include "shell42.h"
#include "hash.h"

char			*hashtable_add(char *key, void **hashtable,
					int hashtable_size, int *index)
{
	char		*path;
	int			i;
	int			hashtable_filled;

	printf("path_search\n");
	path = path_search(key);
	if (!path)
	{
		printf("    no path from path_search\n");
		return (path);
	}
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

	// i = hashfunction(key);
	// if (hashtable[i] != NULL)
	// 	i = collision_hashtable_add(key);
	// hashtable[i] = init_hash_cell(key, path);
	// *index = i;
	return (path);
}

int				hashtable_delete(char *key, void **hashtable,
					int hashtable_size, int hashtable_filled)
{
	int			index;

	printf("deleting an element\n");
	if (hashtable_filled == 0)
		return (HASHTABLE_NF);
	index = hashtable_find(key, hashtable, hashtable_size);
	if (hashtable_delete_invalid(&index, key, hashtable) == HASHTABLE_NF)
	{
		printf("   can not delete an element\n");
		return (HASHTABLE_NF);
	}
	clear_hash_cell(index, hashtable, SLOT_FILLED_HASH);
	return (0);
}

int				hashtable_delete_invalid(int *index, char *key,
					void **hashtable)
{
	t_hashcmd	*slot_ptr;
	int			collision_index;
	
	printf("check if deleting an element is valid\n");
	if (*index == HASHTABLE_NF || hashtable[*index] == NULL)
		return (HASHTABLE_NF);
	slot_ptr = (t_hashcmd*)hashtable[*index];
	if (ft_strcmp(key, slot_ptr->cmd_name) == 0 &&
			slot_ptr->slot_state == SLOT_DELETED_HASH)
		return (HASHTABLE_NF);
	else if (ft_strcmp(key, slot_ptr->cmd_name))
	{
		collision_index = collision_hashtable_find(*index, key);
		if (collision_index == HASHTABLE_NF ||
				hashtable[collision_index] == NULL)
			return (HASHTABLE_NF);
		slot_ptr = (t_hashcmd*)hashtable[collision_index];
		if (ft_strcmp(key, slot_ptr->cmd_name) == 0 &&
			slot_ptr->slot_state == SLOT_DELETED_HASH)
		return (HASHTABLE_NF);
		*index = collision_index;
	}
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
	{
		printf("mistake in hashtable_filled value\n");
		return (0);
	}
	if (hashtable_filled == 0)
		return (0);
	printf("cleaning the table\n");	
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

	hashtable_filled = -1;
	hashtable_filled = get_hashtable_filled();
	if (hashtable_filled < 0)
	{
		printf("    mistake in hashtable_filled value\n");
		return (0);
	}
	change_hashtable_filled_value(1);
	(*slot_ptr)->slot_state = SLOT_FILLED_HASH;
	if (access((*slot_ptr)->cmd_path, X_OK) == -1)
		(*slot_ptr)->cmd_state = CDM_NON_EXEC;
	else
		(*slot_ptr)->cmd_state = 0;
	return (0);
}