#include "readline.h"

int		printc(int c)
{
	return (write(1, &c, 1));
}

int				putcap(char *cap)
{
	char		buff[20];
	char		*ptr;

	ptr = buff;
	tputs(tgetstr(cap, &ptr), 1, printc);
	return (0);
}

int				position_cursor(char *cap, int x, int y)
{
	char		buff[20];
	char		*ptr;

	ptr = buff;
	tputs(tgoto(tgetstr(cap, &ptr), x, y), 1, printc);
	ptr = buff;
	return (0);
}

