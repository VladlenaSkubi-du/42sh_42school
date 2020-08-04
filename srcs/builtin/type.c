#include "shell42.h"
#include "builtin42.h"

int				btin_type(t_ltree *pos)
{
	int			flags;
	
	flags = find_options(2, (char*[]){"", "--help"}, pos->ar_v);
	if (flags == HELP_FLAG)
		return (usage_btin("type"));
	if (flags < 0)
		return (btin_return_exit_status());
	if (pos->ar_c < 1)
		return (0);
	return (btin_type_check_options(pos->ar_v));
}

int				btin_type_error_message(char *option, int error)
{
	char		*error_message;

	error_message = ft_strjoin("type: ", option);
	error_handler(VARIABLE_ERROR | (ERR_HASH_NF << 9), error_message);
	free(error_message);
	return (error);
}

int				btin_type_check_options(char **argv)
{
	int			i;

	i = 0;
	while (argv[++i])
	{
		if (argv[i][0] == '-')
		{
			if (!argv[i][1])
				return (btin_type_error_message(argv[i], VARIABLE_ERROR));
			else if (argv[i][1] == '-' && !argv[i][2])
				return (btin_type_init(&argv[++i]));
		}
		else
			return (btin_type_init(&argv[i]));
	}
	return (0);
}

int				btin_type_init(char **argv)
{
	int			i;
	int			answer;

	i = -1;
	while (argv[++i])
	{
		if (argv[i][0] == '/') /*здесь нужно проверить, что /bin/ls директория,
							если директория, то просто распечатать ее:
							bash-3.2$ type /bin/ls
							/bin/ls is /bin/ls
							если нет, то отправить в btin_type_turn_to_hash
							bash-3.2$ type /bin.ls
							bash: type: /bin.ls: not found
							*/
			printf("проверить абсолютный путь\n");
		else
		{
			answer = btin_check_arg_if_cmd_name(argv[i]); //лежит в builtins/init_structures.c
			if (answer == ARG_ALIAS)
				printf("сообщение про то, что алиас\n");
			else if (answer == ARG_BUILTIN)
				printf("сообщение про то, что билтин\n");
			else
				btin_type_turn_to_hash(argv[i]);
		}
	}
	return (0);
}

int				btin_type_turn_to_hash(char *arg)
{
	int			where_from;
	char		*path;

	where_from = 0;
	path = hashtable_type_init(&where_from, arg);
	if (path == NULL)
		return (btin_type_error_message(arg, VARIABLE_ERROR));
	if (where_from == 0)
		printf("сообщение про путь типа chmod is /bin/chmod\n"); //используй ft_printf
	else
		printf("сообщение про хеш типа ls is hashed (/bin/ls)\n");
	return (0);
}