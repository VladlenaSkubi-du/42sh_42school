#include "readline.h"

int		str_shift(char *str, int shift)
{
	char	*buff;

	buff = (char *)ft_xmalloc(ft_strlen(str));
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
		write(1, "\b", 1);
		g_rline.pos--;
		putcap("sc");
		ft_putstr( g_rline.cmd + g_rline.pos);
		write(1, " \b", 2);
		putcap("rc");
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
	putcap("sc");
	ft_putstr( g_rline.cmd + g_rline.pos);
	putcap("rc");
	sz++;
	g_rline.str_num = count_str_num(); //put it if only we catch the signal SIGWINCH
	return (0);
}

int		count_str_num(void)
{
	struct winsize	screen;
	unsigned int	i;

	i = 1;
	ioctl(1, TIOCGWINSZ, &screen);
	if ((ft_strlen(g_rline.cmd) + g_rline.prompt_len) > screen.ws_col)
	{
		while ((ft_strlen(g_rline.cmd) + g_rline.prompt_len) > screen.ws_col * i)
			i++;
	}
	return (i);
}