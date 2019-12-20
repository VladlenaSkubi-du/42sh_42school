
#include "parser.h"

/*
** Do we include pos_end? This should be discussed
*/

/*
** This function returns positive integer, which is argc, or -1 in case of any
** illegal symbols discovered
*/

char	**get_argv(int argc, size_t pos_start, size_t pos_end)
{

}

int		get_argc(size_t pos_start, size_t pos_end)
{
	size_t	iter;
	int		ret;

	iter = pos_start;
	ret = 0;
	while (iter < pos_end)
	{
		if (g_techline[iter] == 1)
			iter++;
		else if (!g_techline[iter])
		{
			ret++;
			while (!g_techline[iter])
				iter++;
		}
		else
			return (-1);
	}
	return (ret);
}

/*
** It is assumed, that we receive starting and ending position with only space
** specchars. By the way, we also have to process "raw" tabs (maybe as spaces --
** there is no difference)
*/

int		core_exec(size_t pos_start, size_t pos_end)
{
	char	*exec_cmd;
	char	**exec_av;
	int		exec_ac;

	if (!(exec_cmd = (char *)malloc(pos_end - pos_start + 1)))
		return (-1);
	ft_memcpy(exec_cmd, g_cmd + pos_start, pos_end - pos_start);
	if ((exec_ac = get_argc(pos_start, pos_end)) == -1)
		return (-1);
	if (!(exec_av = get_argv(argc, pos_start, pos_end)))
		return (-1);
}
