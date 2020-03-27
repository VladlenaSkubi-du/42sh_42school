#include "shell42.h"
#include "libft_42.h"

size_t			ft_strlenchri(const char *s, char c)
{
	size_t		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}