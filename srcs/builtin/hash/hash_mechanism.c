#include "shell42.h"
#include "hash.h"

static void		**hashtable_array;
static int		hashtable_array_size;

int				hashtable_init(void)
{
	printf("initialisation of the hashtable\n");
	hashtable_array_size = HASHTABLE_LENGTH;
	hashtable_array = (void**)ft_xmalloc(sizeof(void*) * (hashtable_array_size + 1));
	return (0);
}

void			*get_hashtable_value(int *size)
{
	*size = hashtable_array_size;
	return (hashtable_array);
}

int				change_hastable_value(void *hastable_array_new,
					int hashtable_array_size_new)
{
	hashtable_array = hastable_array_new;
	hashtable_array_size = hashtable_array_size_new;
	return (0);
}

int				hashtable_clean(void)
{
	int			i;

	i = 0;
	printf("cleaning the table\n");	
	while (i < hashtable_array_size)
	{
		if (hashtable_array[i] != NULL)
			clear_hash_cell(i);
		i++;
	}
	return (0);
}

t_hashcmd		*init_hash_cell(char *key)
{
	t_hashcmd	*hash_cell;

	hash_cell = (t_hashcmd*)ft_xmalloc(sizeof(t_hashcmd));
	hash_cell->cmd_name = ft_strdup(key);
	hash_cell->cmd_path = NULL;
	hash_cell->number = 0;
	return (hash_cell);
}

void			clear_hash_cell(int index)
{
	t_hashcmd	*hash_cell_ptr;
	
	hash_cell_ptr = (t_hashcmd*)hashtable_array[index];
	free(hash_cell_ptr->cmd_name);
	free(hash_cell_ptr->cmd_path);
	hash_cell_ptr->number = 0;
	free(hashtable_array[index]);
	hashtable_array[index] = NULL;
}