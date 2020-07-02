#include "shell42.h"
#include "builtin42.h"

int					btin_hash(t_ltree *pos)
{
	int				flags;
	
	if (ft_atoi(find_env_value_rdonly("42SH_NONINTERACTIVE")) == 1)
	{
		error_handler(NONINERACTIVE, pos->ar_v[0]);
		return (NONINERACTIVE);
	}
	flags = find_options(2, (char*[]){"rl", "--help"}, pos->ar_v);
	if (flags == 0x10000)
		return (usage_btin("hash"));
	if (pos->ar_c == 1)
		return (btin_hash_list_hashtable());
	return (btin_hash_check_flags(pos->ar_v));
}

int					btin_hash_check_flags(char **argv)
{
	int				i;

	i = 0;
	while (argv[++i])
	{
		if (argv[i][0] == '-')
		{
			if (!argv[i][1])
				return (btin_hash_error_message(argv[i], OPTIONS_REQUIRED));
			else if (argv[i][1] == 'r')
				return (hashtable_clean());
			else if (argv[i][1] == 'l')
				return (btin_hash_list_hashtable());
			else if (argv[i][1] == '-' && !argv[i][2])
				return (btin_hash_add_to_hashtable(&argv[++i]));
		}
		else if (argv[i][0] == '/')
			continue;
		else
			return (btin_hash_add_to_hashtable(&argv[i]));
	}
	printf("nothing is changed in the hashtable\n");
	return (0);
}

int					btin_hash_list_hashtable(void)
{
	printf("list commands from btin\n");
	return (0);
}

int					btin_hash_add_to_hashtable(char **argv)
{
	int				i;

	i = -1;
	while (argv[++i])
	{
		printf("arg is: %s\n", argv[i]);
		if (btin_hash_check_argument(argv[i]) == HASH_INVALID)
		{
			printf("arg is invalid\n");
			continue;
		}
		if (hashtable_add(argv[i]) == NULL)
			btin_hash_error_message(argv[i], VARIABLE_ERROR);
	}
	return (0);
}

int					btin_hash_check_argument(char *arg)
{
	int				i;

	i = -1;
	while (arg[++i])
	{
		if (ft_isalnum(arg[i]) || arg[i] == '_' ||
				(arg[i] == '.' && ft_isalnum(arg[i])))
			return ((check_if_builtin(arg) >= 0) ? HASH_INVALID : 0);
	}
	return (HASH_INVALID);
}

int					btin_hash_error_message(char *option, int error)
{
	char			*error_message;

	error_message = ft_strjoin("hash: ", option);
	if (error == OPTIONS_REQUIRED)
		error_handler(OPTIONS_REQUIRED | (ERR_BTIN_INVALID << 9), error_message);
	else
		error_handler(VARIABLE_ERROR | (ERR_HASH_NF << 9), error_message);
	free(error_message);
	return (error);
}