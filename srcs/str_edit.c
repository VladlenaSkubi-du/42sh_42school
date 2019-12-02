#include "readline.h"

int		str_shift(char *str, int shift)
{
	char	*buff;

	if (!(buff = (char *)malloc(ft_strlen(str))))
		return (-1);
	ft_strcpy(buff, str);
	ft_strcpy(str + shift, buff);
	free(buff);
	return (0);
}

void	backspace_process(size_t *pos)
{
	if (*pos != 0)
	{
		ft_strcpy(g_cmd + *pos - 1, g_cmd + *pos);
		write(1, "\b \b", 3);
		(*pos)--;
	}
}


int		char_add(char c, size_t *pos)
{
	static size_t	size_max = BUFF_SIZE + 1;
	static size_t	size = 0;

	if (size >= size_max)
	{
		if (!(g_cmd = (char *)ft_realloc(g_cmd, size_max, size_max, size_max + BUFF_SIZE)))
			return (-1);
		size_max += BUFF_SIZE;
	}
	if (g_cmd[*pos] != '\0')
	{
		if(str_shift(g_cmd + *pos, 1))
			return (-1);
	}
	g_cmd[*pos] = c;
	(*pos)++;
	size++;
	return (0);
}