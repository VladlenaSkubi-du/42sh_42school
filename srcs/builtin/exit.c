#include "shell42.h"
#include "builtin42.h"

int				btin_exit(t_ltree *pos)
{
	int			status;
	int			i;
	char		*str;

	ft_putendl_fd("exit", STDOUT_FILENO);
	i = 0;
	if (pos->ar_c > 1)
	{
		while (pos->ar_v[1][i])
		{
			if (!(pos->ar_v[1][i] >= '0' && pos->ar_v[1][i] <= '9'))
			{
				str = ft_strjoin(pos->ar_v[0], ": ");
				str = ft_strrejoin(str, pos->ar_v[1]);
				error_handler(SYNTAX_ERROR | (ERR_NUMERIC << 9), str);
				free(str);
				break ;
			}
			i++;
		}
		status = ft_atoi(pos->ar_v[1]);
	}
	else
		status = 0;
	// ft_one_ltree_clear(pos); //почистить все листы
	fill_hist_in_file();
	clean_everything();
	exit(status);
}
