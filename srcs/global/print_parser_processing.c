#include "shell42.h"

void		print_techline(char *cmd, char *techline, int len_tech)
{
	int	i;

	i = -1;
	ft_printf("g_cmd = %s\n", cmd);
	ft_printf("techline cur:");
	while (++i <= len_tech)
		ft_printf("%3d", techline[i]);
	ft_printf("\n");
}
