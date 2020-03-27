#include "shell42.h"
#include "libft_42.h"

void		*ft_xmalloc(size_t size)
{
	void	*ptr;

	if (!(ptr = malloc(size)))
	{
		write(STDERR_FILENO, "No space left\n", 15);
		exit(MALLOC_ERROR);
	}
	ft_bzero(ptr, size);
	return (ptr);
}
