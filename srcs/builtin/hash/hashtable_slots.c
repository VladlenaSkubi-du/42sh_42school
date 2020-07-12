#include "shell42.h"
#include "hash.h"

t_hashcmd		*init_hash_cell(char *key, char *path)
{
	t_hashcmd	*hash_cell;

	hash_cell = (t_hashcmd*)ft_xmalloc(sizeof(t_hashcmd));
	hash_cell->cmd_name = ft_strdup(key);
	hash_cell->cmd_path = ft_strdup(path);
	hash_cell->number = 0;
	hash_cell->cmd_state = 0;
	hash_cell->slot_state = SLOT_FILLED_HASH;
	return (hash_cell);
}

/*
** We can clear hash slots in three ways:
** 1) path and number when the slot is deleted by the user
** 2) cmd_name (key) and full cell when we clear the table if
** the cell has the status SLOT_DELETED_HASH
** 3) cmd_name, cmd_path and full_cell when the cell has
** the status SLOT_FILLED_HASH but we clear the table
** When @delete_key is tated to SLOT_DELETED_HASH - it means
** that we clear hte table (2nd variant)
*/

void			clear_hash_cell(int index,
					void **hashtable, int delete_key)
{
	t_hashcmd	*hash_cell;

	hash_cell = (t_hashcmd*)hashtable[index];
	if (delete_key == SLOT_DELETED_HASH)
	{
		free(hash_cell->cmd_name);
		free(hashtable[index]);
		hashtable[index] = NULL;
	}
	else if (delete_key == SLOT_FILLED_HASH)
	{
		free(hash_cell->cmd_path);
		hash_cell->number = 0;
		hash_cell->cmd_state = 0;
		hash_cell->slot_state = SLOT_DELETED_HASH;
	}
	else
	{
		free(hash_cell->cmd_name);
		free(hash_cell->cmd_path);
		hash_cell->number = 0;
		hash_cell->cmd_state = 0;
		free(hashtable[index]);
		hashtable[index] = NULL;
	}
}