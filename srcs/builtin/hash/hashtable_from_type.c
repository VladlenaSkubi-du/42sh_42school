#include "shell42.h"
#include "hash.h"

char		*hashtable_is_hashed(int *where, char *key)
{
	char	*path;

	path = NULL;
	if (ft_strcmp(key, "new") == 0)
		*where = 0;
	else
		*where = 1;
	
	// if (path == NULL)
	// 	return (path);
	// else if (access(path, X_OK) == -1)
	// {
	// 	free(path);
	// 	return (NULL);
	//}
	return (NULL);
}