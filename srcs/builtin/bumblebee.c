#include "shell42.h"
#include "builtin42.h"

int		btin_bumblebee(void)
{
	int		fd;
	char	*line;
	
	line = NULL;
	if ((fd = open("srcs/builtin/ft_bumblebee", O_RDONLY)) != -1)
	{
		while (ft_gnl(fd, &line) > 0)
		{
			ft_putendl_fd(line, STDOUT_FILENO);
			free(line);
		}
	}
	close (fd);
	return (0);
}
