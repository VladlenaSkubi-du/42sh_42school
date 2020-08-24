/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 16:12:35 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/24 16:35:56 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

int					btin_hash(t_process *pos)
{
	int				flags;
	
	if (ft_atoi(find_env_value("42SH_NONINTERACTIVE")) == 1)
	{
		error_handler(NONINERACTIVE, pos->argv[0]);
		return (BTIN_ERROR);
	}
	flags = find_options(2, (char*[]){"rld", "--help"}, pos->argv);
	if (flags == HELP_FLAG)
		return (usage_btin("hash"));
	if (flags < 0)
		return (BTIN_ERROR);
	if (pos->argc == 1)
		return (btin_hash_list_hashtable());
	return (btin_hash_check_options(pos->argv));
}

int					btin_hash_check_options(char **argv)
{
	int				i;

	i = 0;
	while (argv[++i])
	{
		if (argv[i][0] == '-')
		{
			if (!argv[i][1])
				return (btin_hash_error_message(argv[i], OPTIONS_REQUIRED));
			else if (argv[i][1] == 'r' || argv[i][1] == 'l')
				btin_hash_check_flags(argv[i]);
			else if (argv[i][1] == 'd')
				return ((check_posix_option(argv[i], "rld", btin_hash_error_message) != 0) ?
					BTIN_ERROR : btin_hash_delete_elements(&argv[++i]));
			else if (argv[i][1] == '-' && !argv[i][2])
				return ((argv[i + 1]) ? btin_hash_add_to_hashtable(&argv[++i]) :
					btin_hash_list_hashtable());
		}
		else if (argv[i][0] == '/')
			continue;
		else
			return (btin_hash_add_to_hashtable(&argv[i]));
	}
	return (0);
}

int					btin_hash_check_flags(char *arg)
{
	if (arg[1] == 'r')
		return ((check_posix_option(arg, "rld", btin_hash_error_message) != 0) ?
			BTIN_ERROR : btin_hash_clean_table());
	return ((check_posix_option(arg, "rld", btin_hash_error_message) != 0) ?
		BTIN_ERROR : btin_hash_list_hashtable());
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
	return (BTIN_ERROR);
}

int					btin_hash_clean_table()
{
	void			**hashtable;
	int				hashtable_size;

	hashtable_size = -1;
	hashtable = get_hashtable_value(&hashtable_size);
	if (hashtable_size < 0)
		return (0);
	hashtable_clean(hashtable, hashtable_size);
	return (0);
}