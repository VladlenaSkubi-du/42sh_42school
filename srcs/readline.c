#include "readline.h"

int		display_promt(void)
{
	write(1, "42sh> ", 6);
	return (0);
}

char	*readline(void)
{
	char	*cmd;
	char	buff[BUFF_SIZE + 1];
	char	temp;
	size_t	i;

	cmd = "";
	ft_bzero(buff, BUFF_SIZE + 1);
	if (set_noncanonical_input() == -1)
	{
		ft_putendl_fd("Terminal can't be changed", 2); //исправить
		return (NULL);
	}
	if (display_promt())
		return (NULL);
	// while (read(1, &temp, 1))
	// {
		
	// }
	return (cmd);
}