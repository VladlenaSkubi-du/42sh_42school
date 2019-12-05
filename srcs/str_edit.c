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

void	backspace_process(void)
{
	if (g_rline.pos != 0)
	{
		ft_strcpy(g_rline.cmd + g_rline.pos - 1, g_rline.cmd + g_rline.pos);
		write(1, "\b \b", 3);
		g_rline.pos--;
	}
}


int		char_add(char c)
{
	static size_t	sz_max = CMD_SIZE + 1;
	static size_t	sz = 0;

	if (sz >= sz_max)
	{
		if (!(g_rline.cmd = (char *)ft_realloc(g_rline.cmd, sz_max, sz_max,
			sz_max + CMD_SIZE)))
			return (-1);
		sz_max += CMD_SIZE;
	}
	if (g_rline.cmd[g_rline.pos] != '\0')
	{
		if(str_shift(g_rline.cmd + g_rline.pos, 1))
			return (-1);
	}
	g_rline.cmd[g_rline.pos] = c;
	g_rline.pos++;
	sz++;
	return (0);
}
