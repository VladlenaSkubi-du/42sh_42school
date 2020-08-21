#include "shell42.h"
#include "hash.h"

static void		**hashtable_array;
static int		hashtable_array_size;
static int		hashtable_array_filled;
static int		hashtable_array_limit;

int				hashtable_init(void)
{
	hashtable_array_size = HASHTABLE_LENGTH;
	hashtable_array = (void**)ft_xmalloc(sizeof(void*) *
		(hashtable_array_size + 1));
	hashtable_array_filled = 0;
	hashtable_array_limit = hashtable_array_size / 2 +
		(hashtable_array_size / 2 / 2);
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

int				change_hashtable_filled_value(int times)
{
	hashtable_array_filled += times;
	if (times == 0 || hashtable_array_filled < 0)
	{
		hashtable_array_filled = 0;
		return (0);
	}
	if (times > 0)
	{
		if (hashtable_array_filled / hashtable_array_size < 1 &&
				hashtable_array_filled >= hashtable_array_limit)
		{
			printf("    realloc of the hashtable\n");
			hashtable_array = ft_memrealloc_array(&hashtable_array,
				hashtable_array_size + 1,
				hashtable_array_size * 2 + 1);
			hashtable_array_size = hashtable_array_size * 2 + 1;
			hashtable_array_limit = hashtable_array_size / 2 +
				(hashtable_array_size / 2 / 2);
		}
	}
	return (0);
}