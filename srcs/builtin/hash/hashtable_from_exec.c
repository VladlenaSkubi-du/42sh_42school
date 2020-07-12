#include "shell42.h"
#include "hash.h"

/*
** Is called form the path_init_function - needs path to be returned
*/

char			*hashtable_cmd_init(char *key)
{
	void		**hashtable;
	int			hashtable_size;
	int			index;
	
	hashtable_size = -1;
	hashtable = get_hashtable_value(&hashtable_size);
	if (hashtable_size < 0)
	{
		printf("can's get hashtable value\n");
		return (NULL);
	}
	index = hashtable_find(key, hashtable, hashtable_size);
	if (index == HASHTABLE_NF)
		return (hash_key_not_found(key, hashtable,
			hashtable_size, index));
	return (hashtable_check_valid(index, key, hashtable, hashtable_size));
}

char			*hash_key_not_found(char *key, void **hashtable,
					int hashtable_size, int index)
{
	char		*path;
	t_hashcmd	*slot_ptr;

	path = NULL;
	path = hashtable_add(key, hashtable, hashtable_size, &index);
	if (!path)
	{
		error_handler(COMMAND_NOT_FOUND | (ERR_COMMAND << 9), key);
		return (0);
	}
	slot_ptr = (t_hashcmd*)hashtable[index];
	slot_ptr->slot_state = SLOT_FILLED_HASH;
	slot_ptr->number++;
	if (access(slot_ptr->cmd_path, X_OK) == -1)
	{
		error_handler(COMMAND_NON_EXECUTABLE, slot_ptr->cmd_path);
		return (0);
	}
	//check the cmd-state
	return (path);
}

/*
** Read-only hashtable function - hashtable_filled is not needed
*/

int				hashtable_find(char *key, void **hashtable,
					int hashtable_size)
{
	int			index;
	t_hashcmd	*slot_ptr;
	// int			comparison;
	
	printf("searching a command in hashtable by key\n");
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
	
	// index = hashfunction(key);
	// slot_ptr = (t_hashcmd*)hashtable[index];
	// comparison = ft_strcmp(key, slot_ptr->cmd_name);
	// if (!comparison && slot_ptr->slot_state == SLOT_FILLED_HASH)
	// 	return (index);
	// else if (!comparison && slot_ptr->slot_state != SLOT_FILLED_HASH) //delete
	// {
	// 	printf("Forgot to change the slot state\n");
	// 	return (index);
	// }
	// else if (comparison && slot_ptr->slot_state == SLOT_DELETED_HASH);
	// 	return (collision_hastable_find(index, key));
	return (HASHTABLE_NF);
}

char			*hashtable_check_valid(int index, char *key,
					void **hashtable, int hashtable_size)
{
	t_hashcmd	*slot_ptr;
	
	printf("checking validity of the path found in the hashtable\n");
	slot_ptr = (t_hashcmd*)hashtable[index];
	if (access(slot_ptr->cmd_path, F_OK) == -1)
	{
		clear_hash_cell(index, hashtable, 0);
		return (hash_key_not_found(key, hashtable, hashtable_size, index));
	}
	slot_ptr->number++;
	return (ft_strdup(slot_ptr->cmd_path));
}
