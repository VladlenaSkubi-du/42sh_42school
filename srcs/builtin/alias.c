#include "shell42.h"
#include "builtin42.h"

int					btin_alias(t_ltree *pos)
{
	int				flags;
	
	flags = find_options(1, (char*[]){"--help"}, pos->ar_v);
	if (flags == HELP_FLAG)
		return (usage_btin("alias"));
	if (pos->ar_c < 2)
		return (btin_alias_list_commands());
	btin_alias_check_flags(pos->ar_v);
	return (0);
}

int					btin_alias_check_flags(char **argv)
{
	int				i;

	i = 0;
	while (argv[++i])
	{
		if (argv[i][0] == '-')
		{
			if (!argv[i][1])
				return (btin_alias_error_message(argv[i], VARIABLE_ERROR));
			else if (argv[i][1] == '-' && !argv[i][2])
				return (btin_alias_init(&argv[++i]));
		}
		else
			return (btin_alias_init(&argv[i]));
	}
	printf("nothing is changed in alias table\n");
	return (0);
}

int					btin_alias_error_message(char *option, int error) //если не найдутся случаи c OPTION, можно удалить
{
	char			*error_message;

	error_message = ft_strjoin("alias: ", option);
	// if (error == OPTIONS_REQUIRED)
	// 	error_handler(OPTIONS_REQUIRED | (ERR_BTIN_INVALID << 9), error_message);
	// else
		error_handler(VARIABLE_ERROR | (ERR_HASH_NF << 9), error_message);
	free(error_message);
	return (error);
}

int					btin_alias_init(char **argv)
{
	//чтобы не было варнингов
	argv = NULL;
	printf("alias init\n");
	return (0);
}

int					btin_alias_list_commands(void)
{
	printf("alias listing commands\n");
	return (0);
}

int					check_if_aliased(char *name)
{
	if (name == NULL || name[0] == '\0')
		return (0);
	// if (ft_strcmp(name, ...) == 0)
	// 	return (ARG_ALIAS);
	return (0);
}