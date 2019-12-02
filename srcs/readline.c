#include "readline.h"

/*
** @sy is symbol
** @pos is position in the line
*/

int		readline_choice(char sy, size_t pos)
{
	ctrl_key(sy, pos);
	if (sy == '\033')
		write(1, "BLYAT!\n", 7); // Escape sequence process
	else
		ft_isprint(sy) ? write(1, &sy, 1) : 0;
	if (char_add(sy, &pos))
		return (-1);
	return (0);
}

int		display_promt(void)
{
	write(STDOUT_FILENO, "\033[1;31m42sh\033[0m> ", 18);
	return (0);
}

char	*readline(void)
{
	char	temp;
	size_t	i;

	// if (!(g_cmd = (char *)ft_xmalloc(BUFF_SIZE + 1)))
	// 	return (0);
	// ft_bzero(g_cmd, BUFF_SIZE + 1);

	g_cmd = (char *)ft_xmalloc(BUFF_SIZE + 1);
	i = 0;
	if (set_noncanonical_input() == -1)
	{
		ft_putendl_fd("Terminal can't be changed", 2); //исправить
		return (NULL);
	}
	if (display_promt())
		return (NULL);
	while (read(1, &temp, 1) && temp != '\n')
	{
		if (readline_choice(temp, i) < 0)
			return (NULL);
		i++;
	}
	return (g_cmd);
}