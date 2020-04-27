#include "shell42.h"
#include "libft_42.h"

int				ft_strchrdiff(const char *s1, const char *s2, char sy)
{
	int i;

	if (s1 == 0 || s2 == 0)
		return (0);
	else if (*s1 == '\0' && *s2 == '\0')
		return (1);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && s1[i] != sy)
		i++;
	if ((s1[i] == '\0' || s1[i] == sy) && !(s2[i] == '\0'))
		return (0);
	return (1);
}