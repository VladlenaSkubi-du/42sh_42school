#include "shell42.h"
#include "hash.h"

static void		**hashtable_array;
static int		hashtable_array_size;
static int		hashtable_array_filled;

int				hashtable_init(void)
{
	printf("initialisation of the hashtable\n");
	hashtable_array_size = HASHTABLE_LENGTH;
	hashtable_array = (void**)ft_xmalloc(sizeof(void*) *
		(hashtable_array_size + 1));
	hashtable_array_filled = 0;
	return (0);
}

void			**get_hashtable_value(int *size)
{
	*size = hashtable_array_size;
	return (hashtable_array);
}

int				get_hashtable_filled(void)
{
	return (hashtable_array_filled);
}

int				change_hastable_value(void **hastable_array_new,
					int hashtable_array_size_new)
{
	hashtable_array = hastable_array_new;
	hashtable_array_size = hashtable_array_size_new;
	return (0);
}

int				change_hashtable_filled_value(int times)
{
	if (times == 0)
	{
		hashtable_array_filled = 0;
		return (0);
	}
	hashtable_array_filled += times;
	if (hashtable_array_filled < 0)
		hashtable_array_filled = 0;
	return (0);
}