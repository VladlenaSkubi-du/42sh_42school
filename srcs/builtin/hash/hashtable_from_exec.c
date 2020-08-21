#include "shell42.h"
#include "hash.h"

/*
** Is called form the path_init_function - needs path to be returned
** path can be NULL or a malloced char*
*/

char			*hashtable_cmd_init(char *key)
{
	void		**hashtable;
	int			hashtable_size;
	int			index;
	
	hashtable_size = -1;
	hashtable = get_hashtable_value(&hashtable_size);
	if (hashtable_size < 0)
		return (NULL);
	index = hashtable_find(key, hashtable, hashtable_size);
	if (index == HASHTABLE_NF)
		return (hash_key_not_found(key, hashtable,
			hashtable_size, index));
	return (hashtable_check_valid(index, key, hashtable, hashtable_size));
}

/*
** Here we search a command according to the PATH value
** @path can be NULL or a malloced char*
** If @path has a path-value and in hashtable_add a new slot was added,
** slot is updated and thee number of address to the command grows
** If command is non-executable, it is noted in the table and
** an error is returned
*/

char			*hash_key_not_found(char *key, void **hashtable,
					int hashtable_size, int index)
{
	char		*path;
	t_hashcmd	*slot_ptr;

	path = hashtable_add(key, hashtable, hashtable_size, &index);
	if (!path)
	{
		error_handler(COMMAND_NOT_FOUND | (ERR_COMMAND << 9), key);
		return (NULL);
	}
	slot_ptr = (t_hashcmd*)hashtable[index];
	update_hashtable_slot_filled(&slot_ptr);
	slot_ptr->number++;
	if (slot_ptr->cmd_state == CDM_NON_EXEC)
	{
		free(path);
		error_handler(COMMAND_NON_EXECUTABLE |
			(ERR_NO_ACC << 9), slot_ptr->cmd_path);
		return (NULL);
	}
	slot_ptr->cmd_state = 0;
	return (path);
}

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

/*
** If we do not find a cmd by the path saved in the table or
** the cmd is non-executable - we try to find an executable one
** If we find the path and it is valid, we increase the number
** of address to the cmd and return the path-value
*/

char			*hashtable_check_valid(int index, char *key,
					void **hashtable, int hashtable_size)
{
	t_hashcmd	*slot_ptr;
	
	slot_ptr = (t_hashcmd*)hashtable[index];
	if (access(slot_ptr->cmd_path, F_OK) == -1 ||
			access(slot_ptr->cmd_path, X_OK) == -1)
	{
		printf("    command saved in hashtable is invalid\n");
		clear_hash_cell(index, hashtable, 0);
		return (hash_key_not_found(key, hashtable, hashtable_size, index));
	}
	slot_ptr->number++;
	return (ft_strdup(slot_ptr->cmd_path));
}
