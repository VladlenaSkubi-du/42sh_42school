/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 16:42:44 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/24 16:28:02 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

int				btin_type(t_process *pos)
{
	int			flags;

	flags = find_options(2, (char*[]){"", "--help"}, pos->argv);
	if (flags == HELP_FLAG)
		return (usage_btin("type"));
	if (flags < 0)
		return (BTIN_ERROR);
	if (pos->argc < 1)
		return (0);
	return (btin_type_check_options(pos->argv));
}

int				btin_type_error_message(char *option, int error)
{
	char		*error_message;

	error_message = ft_strjoin("type: ", option);
	error_handler(VARIABLE_ERROR | (ERR_HASH_NF << 9), error_message);
	free(error_message);
	return (BTIN_ERROR);
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
		if (argv[i][0] == '/')
		{
			if (!access(argv[i], 1))
				ft_printf("%s is %s\n", argv[i], argv[i]);
			else
				return (btin_type_error_message(argv[i], VARIABLE_ERROR));
		}
		else
		{
			answer = btin_check_arg_if_cmd_name(argv[i]);
			if (answer == ARG_ALIAS)
				ft_printf("%s is alias\n", argv[i]);
			else if (answer == ARG_BUILTIN)
				ft_printf("%s is a shell builtin\n", argv[i]);
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
		ft_printf("%s is %s\n", arg, path);
	else
		ft_printf("%s is hashed (%s)\n", arg, path);
	return (0);
}
