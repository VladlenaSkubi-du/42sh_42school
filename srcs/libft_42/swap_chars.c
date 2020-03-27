#include "shell42.h"
#include "libft_42.h"

void		swap_chars(char *cmd, int b, int a)
{
	char	tmp;

	tmp = cmd[b];
	cmd[b] = cmd[a];
	cmd[a] = tmp;
}
