#include "shell42.h"
#include "builtin42.h"

int					btin_unalias(t_ltree *pos)
{
	int				flags;
	
	flags = find_options(2, (char*[]){"-a", "--help"}, pos->ar_v);
	if (flags == HELP_FLAG || pos->ar_c < 2)
		return (usage_btin("unalias"));
	if (flags < 0)
		return (btin_return_exit_status()); //если возвращается отрицательные flags, значит,
		//ошибка уже была выведена и нужно просто выйти из функции, ошибка OPTIONS_REQUIRED
	return (btin_unalias_check_flags(pos->ar_v));
}

int					btin_unalias_check_flags(char **argv)
{
	int				i;

	i = 0;
	while (argv[++i])
	{
		if (argv[i][0] == '-')
		{
			if (!argv[i][1])
				return (btin_unalias_error_message(argv[i], VARIABLE_ERROR));
			else if (argv[i][1] == 'a')
			{
				if (check_posix_option(argv[i], 'a', btin_unalias_error_message) != 0)
					return (OPTIONS_REQUIRED);
				return (btin_unalias_clean_commands());
			}
			else if (argv[i][1] == '-' && !argv[i][2])
				return (btin_unalias_init(&argv[++i]));
		}
		else
			return (btin_unalias_init(&argv[i]));
	}
	printf("nothing is changed in alias table\n");
	return (0);
}

int					btin_unalias_error_message(char *option, int error)
{
	char			*error_message;

	error_message = ft_strjoin("unalias: ", option);
	if (error == OPTIONS_REQUIRED)
		error_handler(OPTIONS_REQUIRED | (ERR_BTIN_INVALID << 9), error_message);
	else
		error_handler(VARIABLE_ERROR | (ERR_HASH_NF << 9), error_message);
	free(error_message);
	return (error);
}


int					btin_unalias_init(char **argv)
{
	//чтобы не было варнингов
	argv = NULL;
	printf("unalias init\n");
	return (0);
}

int					btin_unalias_clean_commands(void)
{
	printf("cleaning the aliased commands\n");
	return (0);
}
