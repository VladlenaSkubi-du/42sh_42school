#include "readline.h"

int		printc(int c)
{
	return (write(1, &c, 1));
}

int		putcap(char *cap)
{
	char	buff[16];
	char	*ptr;

	ptr = buff;
	tputs(tgetstr(cap, &ptr), 1, printc);
	return (0);
}

int		noncanonical_input(int mode)
{
	struct termios			new;
	static struct termios	save;

	if (mode)
	{
		tcgetattr(2, &new);
		tcgetattr(2, &save);
		new.c_lflag &= ~(ICANON | ECHO);
		new.c_cc[VMIN] = 1;
		new.c_cc[VTIME] = 0;
		tcsetattr(2, TCSANOW, &new);
	}
	else
		tcsetattr(2, TCSANOW, &save);
	return (0);
}

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
	if (noncanonical_input(1))
		return (0);
	if (display_promt())
		return (0);
	while (read(1, &temp, 1))
	{
		
	}
}