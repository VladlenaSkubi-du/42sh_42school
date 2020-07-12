#include "shell42.h"
#include "builtin42.h"

int					btin_hash_list_hashtable(void)
{
	int				i;
	t_hashcmd		*slot_ptr;
	void			**hashtable;
	int				hashtable_size;

	i = 0;
	hashtable_size = -1;
	hashtable = get_hashtable_value(&hashtable_size);
	if (hashtable_size < 0)
	{
		printf("can's get hashtable value\n");
		return (0);
	}
	printf("list commands from btin\n"); //DELETE
	printf("%10s%s%s\n", "hits", "    ", "command");
	while (i < hashtable_size)
	{
		if (hashtable[i] != NULL)
		{
			slot_ptr = (t_hashcmd*)hashtable[i];
			if (slot_ptr->slot_state == SLOT_FILLED_HASH)
				printf("%10d%s%s\n", slot_ptr->number, "    ",
					slot_ptr->cmd_path);
			//печатать сообщение, если команда недоступна
		}
		i++;
	}	
	return (0);
}

int					btin_hash_delete_elements(char **argv)
{
	int				i;
	
	i = 0;
	while (argv[i])
	{
		printf("arg is: %s\n", argv[i]);
		if (btin_hash_check_argument(argv[i]) == HASH_INVALID)
		{
			printf("arg is invalid\n");
			continue;
		}
		btin_hash_valid_argument_delete(argv[i]);
	}
	return (0);
}

int					btin_hash_add_to_hashtable(char **argv)
{
	int				i;

	i = -1;
	while (argv[++i])
	{
		printf("arg is: %s\n", argv[i]);
		if (btin_hash_check_argument(argv[i]) == HASH_INVALID)
		{
			printf("arg is invalid\n");
			continue;
		}
		btin_hash_valid_argument_add(argv[i]);
	}
	return (0);
}

int					btin_hash_valid_argument_add(char *key)
{
	int				index;
	void			**hashtable;
	int				hashtable_size;
	char			*path;
	t_hashcmd		*slot_ptr;

	hashtable_size = -1;
	index = -1;
	hashtable = get_hashtable_value(&hashtable_size);
	if (hashtable_size < 0)
	{
		printf("can's get hashtable value\n");
		return (0);
	}
	path = hashtable_add(key, hashtable, hashtable_size, &index);
	if (path == NULL)
		btin_hash_error_message(key, VARIABLE_ERROR);
	else
	{
		slot_ptr = (t_hashcmd*)hashtable[index];
		slot_ptr->slot_state = SLOT_FILLED_HASH;
		slot_ptr->number = 0;
	}
	//проверка доступа
	return (0);
}

int				btin_hash_valid_argument_delete(char *key)
{
	int				index;
	void			**hashtable;
	int				hashtable_size;
	int				hashtable_filled;

	hashtable_size = -1;
	index = -1;
	hashtable = get_hashtable_value(&hashtable_size);
	if (hashtable_size < 0)
	{
		printf("can's get hashtable value\n");
		return (0);
	}
	hashtable_filled = get_hashtable_filled();
	index = hashtable_delete(key, hashtable, hashtable_size, hashtable_filled);
	if (index != HASHTABLE_NF)
		change_hashtable_filled_value(-1);
	else
		printf("Error to make: there is no such command in hashtable\n");
	return (0);
}