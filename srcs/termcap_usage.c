#include "readline.c"

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