#include "shell42.h"
#include "builtin42.h"

int		ft_check_cd_args(char **argv, int i)
{
	if (argv[i] && argv[i + 1])
	{
		ft_error(NULL, 5);
		return (1);
	}
	return (0);
}

int		ft_valid_cd(char **argv, int i) //make sth with this shit from ass
{
	if (ft_check_cd_args(argv, i))
		return (1);
	return (0);
}
