#include "shell42.h"
#include "hash.h"

char			*hashtable_cmd_init(char *key)
{
	int			index;
	char		*path;
	
	if ((index = hashtable_find(key)) == HASHTABLE_NF)
	{
		path = hashtable_add(key); /*exec*/
		if (path != NULL)
			printf("increasing a number of turning to cmd\n");
		return (path);
	}
	if (hashtable_check_valid(index, key) == HASH_INVALID)
		return (hashtable_change(index, key));
	printf("increasing a number of turning to cmd\n");
	return (0);
}

int				hashtable_find(char *key)
{
	int			index;
	
	printf("searching a command in hashtable by key\n");
	index = hashfunction(key);

	//as a try
	if (ft_strncmp(key, "old", 3) == 0)
		return (0);
	else if (ft_strncmp(key, "new", 3) == 0)
		return (HASHTABLE_NF);

	return (0);
}

char			*hashtable_add(char *key)
{
	char		*path;

	printf("path_search\n");
	path = NULL;

	//as a try
	if (ft_strcmp(key, "newyes") == 0)
		printf("adding a command to hashtable by key\n");
	else if (ft_strcmp(key, "newno") == 0)
	{
		printf("can't add a command, the path is NULL - not found\n");
		return (NULL);
	}
	return (NULL);
}

int				hashtable_check_valid(int index, char *key)
{
	printf("checking validity of the path found in the hashtable\n");

	//as a try
	if (ft_strcmp(key, "oldyes") == 0)
	{
		printf("the path is valid\n");
		return (0);
	}
	else if (ft_strcmp(key, "oldno") == 0)
	{
		printf("the path is INvalid\n");
		return (HASH_INVALID);
	}
	return (0);
}

char			*hashtable_change(int index, char *key)
{
	char		*path;
	
	path = NULL;
	printf("changing the value of path\n");
	printf("path_search\n");
	/* if ((path == path_search()) == NULL)
		...[index] = NULL;
	else
	{
		...[index] = (t_hashcmd*)init_hash_cell();
		...[index]->cmd_path = path;
	}*/
	printf("making the number one again because of the new path\n");
	return (path);
}
