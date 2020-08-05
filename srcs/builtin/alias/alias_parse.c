/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 15:08:22 by rbednar           #+#    #+#             */
/*   Updated: 2020/08/05 17:47:33 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

/*
** In the shell command language, a word consisting solely of underscores, 
** digits, and alphabetics from the portable character set and any of the
** following characters: '!', '%', ',', '@'.
*/

char	*find_in_alias(t_list **arr, char *name)
{
	size_t	tmp;
	size_t	len_name;
	t_list	*start;

	len_name = ft_strlen(name);
	if (!arr || !len_name)
		return (NULL);
	start = *arr;
	while (arr)
	{
		tmp = ft_strchri((char *)(start->content), '=');
		if (ft_strncmp((char *)(start->content), name, len_name) == 0 &&
			tmp == len_name)
			return ((char *)(start->content));
		start = start->next;
	}
	return (NULL);
}

int		btin_alias_save(t_list **buf, char *arg, int eq)
{
	char	*name;
	char	*tmp;

	tmp = NULL;
	name = ft_strndup(arg, eq);
	if (btin_alias_valid_name(name))
		ft_lstadd(buf, ft_lstnew(ft_strdup(arg), ft_strlen(arg) + 1));
	else
	{
		tmp = ft_strdup("`");
		tmp = ft_strrejoin(tmp, name);
		tmp = ft_strrejoin(tmp, "': invalid alias name\n");
		btin_alias_error_message(tmp, 1);
	}
	free(tmp);
	free(name);
	return (0);
}

int		btin_alias_print_one(char *arg)
{
	char	*ans;
	char	*tmp;

	tmp = NULL;
	btin_alias_init(&arg, &ans, ASSIGN);
	if (ans)
	{
		tmp = ft_xmalloc(sizeof(char) * (ft_strlen(ans) + 3));
		ft_strcat(tmp, arg);
		ft_strcat(tmp, "'");
		ft_strcat(tmp, &ans[ft_strlen(tmp)]);
		ft_strcat(tmp, "'");
		ft_putendl_fd(tmp, STDOUT_FILENO);
		free(ans);		
	}
	else
	{
		tmp = strdup(arg);
		tmp = ft_strrejoin(tmp, ": not found\n");
		btin_alias_error_message(tmp, 1);
	}
	free(tmp);
	return (0);
}

int		btin_alias_merge_buf(t_list **arr, t_list **buf)
{
	return (0);
}

int		btin_alias_list_commands(void)
{
	printf("alias listing commands\n");
	return (0);
}
