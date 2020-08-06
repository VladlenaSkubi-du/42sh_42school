/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 16:59:53 by rbednar           #+#    #+#             */
/*   Updated: 2020/08/06 17:06:49 by rbednar          ###   ########.fr       */
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
		return (btin_alias_init(NULL, NULL, PRINT));
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

/*
** Main function to work with aliases. It uses flag to check option:
** SAVE - init arrays
** CONTINUE - save buf array into alias array
** DEL_ALL - clean alias array
** ASSIGN - get alias string in "char *ans"
** PRINT - print all aliases from alias array in posix form
** MINUS - del one alias by name from alias array
*/

int		btin_alias_init(char **argv, char **ans, int flag)
{
	static t_list	*alias;
	static t_list	*buf;
	int				i;

	(flag == SAVE) ? alias = NULL : 0;
	(flag == SAVE) ? buf = NULL : 0;
	i = -1;
	if (flag == LINE)
		while (argv[++i])
		{
			if ((flag = ft_strchri(argv[i], '=')) > 0)
				btin_alias_save(&buf, argv[i], flag);
			else
				btin_alias_print_one(argv[i]);
		}
	else if (flag == CONTINUE)
		btin_alias_copy_buf(&alias, &buf);
	else if (flag == DEL_ALL)
		btin_alias_delete_all(&buf);
	else if (flag == MINUS)
		btin_alias_delete(&buf, *argv);
	else
		return (btin_alias_print(&alias, argv, ans, flag));
	return (0);
}

/*
** Continue of btin_alias_init
*/

int		btin_alias_print(t_list **alias, char **argv, char **ans, int flag)
{
	char	*eq;
	t_list	*start;
	char	*tmp;

	if (flag == ASSIGN)
	{
		eq = find_in_alias(alias, argv[0]);
		return ((*ans = ft_strdup(eq)) ? 0 : OUT);
	}
	else if (flag == PRINT)
	{
		start = *alias;
		while (start)
		{
			tmp = btin_alias_line_form((char *)start->content);
			ft_putendl_fd(tmp, STDOUT_FILENO);
			free(tmp);
			start = start->next;
		}
	}
	return (0);
}
