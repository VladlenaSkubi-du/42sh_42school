#include "shell42.h"
#include "readline.h"

int					init_completion(void)
{
	g_compl.to_compl = ft_strndup(g_rline.cmd, g_rline.pos);
	g_compl.len_tocompl = ft_strlen(g_compl.to_compl);
	g_compl.menu = NULL;
	g_compl.total = 0;
	g_compl.tablevel = 0;
	g_compl.to_del = 0;
	g_compl.menu_buffer.buffer = NULL;
	return (0);
}

/*
** If there are no options for completion, we clear the 
** allocated @g_complete and @g_techline strings and ring
** the bell
*/

int					clear_completion(int flag)
{
	free(g_compl.to_compl);
	g_compl.to_compl = NULL;
	g_compl.len_tocompl = 0;
	if (g_compl.menu != NULL)
	{
		ft_arrdel(g_compl.menu);
		g_compl.menu = NULL;
	}
	g_compl.total = 0;
	g_compl.tablevel = 0;
	g_compl.to_del = 0;
	if (g_compl.menu_buffer.buffer != NULL)
	{
		ft_arrdel(g_compl.menu_buffer.buffer);
		g_compl.menu_buffer.buffer = NULL;
	}
	return ((flag == 1) ? incorrect_sequence() : 0);
}

char				*path_parse_compl(void) //to DELETE
{
	int				i;

	i = 0;
	while (g_env[i])
	{
		if (ft_strncmp(g_env[i], "PATH=", 5) == 0)
			return (g_env[i] + 5);
		i++;
	}
	return (NULL);
}