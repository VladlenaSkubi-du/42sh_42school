#include "shell42.h"
#include "builtin42.h"

//при удалении ячейки чистится память в пути и номер становится дефолтным
//флаг меняется на удален
//при добавлении строки с флагом удален мы чистим ячейку полностью и маллочим заново
//новыми значениями, если ячейка пустая, то маллочим сразу
//при полной очистке хеш-таблицы мы удаляем все ячейки (там, где флаг полон - полностью
//там, где удален - только ключ)
//если permisson denied, то первое обращение итерируется до 1, а последующие нет, ошибка при вызове
//если нет в хеше, но заносят prmission denied  в хеш, пишется, что не найдено. если уже есть в хеше,
//но снова пытаются внести permission denied, пишет ошибку - плохо

//type: если есть в хе-таблице, возвращаю, что в хеш-таблице существует и путь
//нет  в хеш таблице - полный поиск пути
//нет в хеш-таблице и нет прав - type: ls: not found
//есть в хеш-таблице, но нет доступа - сущ-ет в хеше и путь

int					btin_hash(t_ltree *pos)
{
	int				flags;
	
	if (ft_atoi(find_env_value("42SH_NONINTERACTIVE")) == 1)
	{
		error_handler(NONINERACTIVE, pos->ar_v[0]);
		return (NONINERACTIVE);
	}
	flags = find_options(2, (char*[]){"rld", "--help"}, pos->ar_v);
	if (flags == 0x10000) //change (shit from ass)
		return (usage_btin("hash"));
	if (flags < 0)
		return (btin_return_exit_status());
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
				return (btin_hash_clean_table());
			else if (argv[i][1] == 'l')
				return (btin_hash_list_hashtable());
			else if (argv[i][1] == 'd') //проверка аргументов
				return (btin_hash_delete_elements(&argv[++i]));
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

int					btin_hash_clean_table()
{
	void			**hashtable;
	int				hashtable_size;

	hashtable_size = -1;
	hashtable = get_hashtable_value(&hashtable_size);
	if (hashtable_size < 0)
	{
		printf("can's get hashtable value\n");
		return (0);
	}
	hashtable_clean(hashtable, hashtable_size);
	return (0);
}