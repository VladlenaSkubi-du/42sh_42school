#include "readline.h"

int		display_promt(void)
{
	write(1, "42sh> ", 6);
	return (0);
}

char	*readline(void)
{
	char	temp;
	size_t	i;

	if (!(g_cmd = (char *)malloc(BUFF_SIZE + 1)))
		return (0);
	i = 0;
	ft_bzero(g_cmd, BUFF_SIZE + 1);
	if (set_noncanonical_input() == -1)
	{
		ft_putendl_fd("Terminal can't be changed", 2); //исправить
		return (NULL);
	}
	if (display_promt())
		return (NULL);
	while (read(1, &temp, 1) && temp != '\n')
	{
		if (temp == '\033')
			write(1, "BLYAT!\n", 7);// Escape sequence process
		else
			ft_isprint(temp) ? write(1, &temp, 1) : 0;
		if (temp == 127)
			backspace_process(&i);
		else if (char_add(temp, &i))
			return (0);
	}
	return (g_cmd);
}