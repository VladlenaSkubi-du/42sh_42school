#include "shell42.h"
#include "libft_42.h"

char		*ft_straddsy(char *dest, char sy)
{
	int		i;

	i = 0;
	while (dest[i])
		i++;
	dest[i] = sy;
	return (dest);
}
