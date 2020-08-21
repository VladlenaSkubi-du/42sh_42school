#include "shell42.h"

char			*hashtable_add_hash(char *key, void **hashtable,
					int hashtable_size, int *index)
{
	char		*path;
	int			i;
	int			hashtable_filled;

	path = path_search(key);
	if (!path)
		return (NULL);
	hashtable_filled = get_hashtable_filled();
	i = hashfunction(key);
	if (hashtable[i] != NULL)
		i = collision_hashtable_add(key);
	hashtable[i] = init_hash_cell(key, path);
	*index = i;
	return (path);
}

int				hashtable_delete_hash(char *key, void **hashtable,
					int hashtable_size, int hashtable_filled)
{
	int			index;

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

/*
** If there is nothing lying in the hashtable cell
** If such cell was deleted (key lies but the slot is deleted)
** If the cell that index point to does not refer to the
** key stated and after the search we found that such cell
** does not exist or was deleted
** - we return the answer: HASHTABLE_NF
*/

int				hashtable_delete_invalid_hash(int *index, char *key,
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

/*
** Read-only hashtable function - hashtable_filled is not needed
*/

int				hashtable_find(char *key, void **hashtable,
					int hashtable_size)
{
	int			index;
	t_hashcmd	*slot_ptr;
	int			comparison;

	index = hashfunction(key);
	slot_ptr = (t_hashcmd*)hashtable[index];
	comparison = ft_strcmp(key, slot_ptr->cmd_name);
	if (!comparison && slot_ptr->slot_state == SLOT_FILLED_HASH)
		return (index);
	else if (!comparison && slot_ptr->slot_state != SLOT_FILLED_HASH) //delete
	{
		printf("Forgot to change the slot state\n");
		return (index);
	}
	else if (comparison && slot_ptr->slot_state == SLOT_DELETED_HASH);
		return (collision_hastable_find(index, key));
	return (HASHTABLE_NF);
}