/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 16:59:53 by rbednar           #+#    #+#             */
/*   Updated: 2020/08/05 16:50:45 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

int		btin_alias(t_ltree *pos)
{
	int	flags;
	
	flags = find_options(2, (char*[]){"", "--help"}, pos->ar_v);
	if (flags == HELP_FLAG)
		return (usage_btin("alias"));
	if (flags < 0)
		return (btin_return_exit_status());
	if (pos->ar_c < 2)
		return (btin_alias_list_commands());
	return (btin_alias_check_options(pos->ar_v));
}

int		btin_alias_check_options(char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		if (argv[i][0] == '-')
		{
			if (!argv[i][1])
				return (btin_alias_error_message(argv[i], VARIABLE_ERROR));
			else if (argv[i][1] == '-' && !argv[i][2])
				return (btin_alias_init(&argv[++i], NULL, LINE));
		}
		else
			return (btin_alias_init(&argv[i], NULL, LINE));
	}
	printf("WARNING nothing is changed in alias table\n");
	return (0);
}

int		btin_alias_error_message(char *option, int error)
{
	char	*error_message;

	error_message = ft_strjoin("alias: ", option);
	error_handler(VARIABLE_ERROR, error_message);
	free(error_message);
	return (error);
}

int		btin_alias_init(char **argv, char **ans, int flag)
{
	static t_list	*alias;
	static t_list	*buf;
	int				i;
	char			*eq;

	(flag == SAVE) ? alias = NULL : 0;
	(flag == SAVE) ? buf = NULL : 0;
	i = -1;
	if (flag == LINE)
		while(argv[++i])
		{
			if ((flag = ft_strchri(argv[i], '=')) > 0)
				btin_alias_save(&buf, argv[i], flag);
			else
				btin_alias_print_one(argv[i]);
		}
	else if (flag == ASSIGN)
	{
		if ((eq = find_in_alias(&alias, argv[0])))
			return ((*ans = ft_strdup(eq)) ? 0 : OUT);
		return(OUT);
	}
	else if (flag == CONTINUE)
		btin_alias_merge_buf(&alias, &buf);
	return (0);
}

int		check_if_aliased(char *name)
{
	if (name == NULL || name[0] == '\0')
		return (0);
	// if (ft_strcmp(name, ...) == 0)
	// 	return (ARG_ALIAS);
	return (0);
}