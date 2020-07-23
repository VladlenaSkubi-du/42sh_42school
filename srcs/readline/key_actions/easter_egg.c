#include "shell42.h"
#include "readline.h"

int				kirill_lgbt(void)
{
	int			i;
	char		*color;
	char		*kirill;

	kirill = ft_strstr(g_rline.cmd, "kirill");
	if (kirill != NULL && g_rline.pos > 5 &&
		g_rline.cmd[g_rline.pos - 1] == 'l' &&
		g_rline.cmd[g_rline.pos - 2] == 'l')
	{
		i = -1;
		while (++i < 6)
			backspace_process();
		kirill = "kirill";
		i = -1;
		while (++i < 6)
		{
			color = colors_process(i);
			char_add(kirill[i], color);
		}
	}
	return (0);
}
