#include "shell42.h"
#include "builtin42.h"

int					btin_hash_list_hashtable(void)
{
	void			**hashtable;
	int				hashtable_size;
	int				hashtable_filled;
	int				i;

	hashtable_size = -1;
	hashtable = get_hashtable_value(&hashtable_size);
	if (hashtable_size < 0)
	{
		printf("    can's get hashtable value\n");
		return (0);
	}
	hashtable_filled = get_hashtable_filled();
	if (hashtable_size == 0 || hashtable_filled == 0)
		return (0);
	// printf("list commands from btin\n"); //DELETE
	ft_printf("%6s%s%s\n", "hits", "    ", "command");
	i = -1;
	while (++i < hashtable_size)
	{
		if (hashtable[i] == NULL)
			continue ;
		print_hash_cell(i, hashtable);
	}
	return (0);
}

int					btin_hash_delete_elements(char **argv)
{
	int				i;
	int				answer;
	
	i = -1;
	while (argv[++i])
	{
		// printf("    arg is: %s\n", argv[i]);
		answer = btin_check_arg_if_cmd_name(argv[i]);
		if (answer == ARG_INVALID || answer == ARG_ALIAS ||
				answer == ARG_BUILTIN)
		{
			printf("    arg is invalid\n");
			continue;
		}
		btin_hash_valid_argument_delete(argv[i]);
	}
	return (0);
}

int					btin_hash_valid_argument_delete(char *key)
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
		printf("    can's get hashtable value\n");
		return (0);
	}
	hashtable_filled = get_hashtable_filled();
	index = hashtable_delete(key, hashtable, hashtable_size, hashtable_filled);
	if (index == HASHTABLE_NF)
		return (btin_hash_error_message(key, VARIABLE_ERROR));
	change_hashtable_filled_value(-1);
	return (0);
}

int					btin_hash_add_to_hashtable(char **argv)
{
	int				i;
	int				answer;

	i = -1;
	while (argv[++i])
	{
		// printf("    arg is: %s\n", argv[i]);
		answer = btin_check_arg_if_cmd_name(argv[i]);
		if (answer == ARG_INVALID || answer == ARG_ALIAS ||
				answer == ARG_BUILTIN)
		{
			printf("    arg is invalid\n");
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
	path = NULL;
	hashtable = get_hashtable_value(&hashtable_size);
	if (hashtable_size < 0)
	{
		printf("    can's get hashtable value\n");
		return (0);
	}
	index = hashtable_find(key, hashtable, hashtable_size);
	if (index == HASHTABLE_NF)
	{
		path = hashtable_add(key, hashtable, hashtable_size, &index);
		if (path == NULL)
			return (btin_hash_error_message(key, VARIABLE_ERROR));
	}
	slot_ptr = (t_hashcmd*)hashtable[index];
	update_hashtable_slot_filled(&slot_ptr);
	slot_ptr->number = 0;
	free(path);
	return (0);
}
