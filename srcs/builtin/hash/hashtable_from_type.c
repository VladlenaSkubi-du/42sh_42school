#include "shell42.h"
#include "hash.h"

/*
** Returns NULL or full path to a key (command)
** returns NULL is command is not found in hashtable and after
** PATH parsing
** returns path is the command is hashed (where changes to 1)
** or if command is not hashed but found in PATH parsing - only
** if it is executable (where is changed to 0)
*/

char		*hashtable_type_init(int *where, char *key)
{
	char	*path;
	void	**hashtable;
	int		hashtable_size;
	int		index;
	
	path = NULL;
	hashtable_size = -1;
	hashtable = get_hashtable_value(&hashtable_size);
	if (hashtable_size < 0)
	{
		printf("can's get hashtable value\n");
		return (NULL);
	}
	index = hashtable_find(key, hashtable, hashtable_size);
	if (index == HASHTABLE_NF)
	{
		path = hashtable_key_nf_type(key, hashtable, hashtable_size);
		*where = 0;
		return ((path == NULL) ? NULL : path);
	}
	hashtable_check_valid_type(index, key, hashtable, hashtable_size);
	return (path);
}

char		*hashtable_key_nf_type(char *key, void **hashtable,
				int hashtable_size)
{
	return (NULL);
}

int			hashtable_check_valid_type(int index, char *key,
				void **hashtable, int hashtable_size)
{
	return (0);
}