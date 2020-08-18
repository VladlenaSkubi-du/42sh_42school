/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 15:08:22 by rbednar           #+#    #+#             */
/*   Updated: 2020/08/07 20:29:58 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

/*
** Uses to find alias by name in alias array.
*/

char	*find_in_alias(t_list **arr, char *name)
{
	size_t	tmp;
	size_t	len_name;
	t_list	*start;

	len_name = ft_strlen(name);
	if (!*arr || !*name)
		return (NULL);
	start = *arr;
	while (start)
	{
		tmp = ft_strchri((char *)(start->content), '=');
		if (ft_strncmp((char *)(start->content), name, len_name) == 0 &&
			tmp == len_name)
			return ((char *)(start->content));
		start = start->next;
	}
	return (NULL);
}

/*
** Uses to save alias in alias array or to print error if name is invalid
*/

int		btin_alias_save(t_list **buf, char *arg, int eq)
{
	char	*name;
	char	*tmp;

	tmp = NULL;
	name = ft_strndup(arg, eq);
	if (btin_alias_valid_name(name))
		btin_alias_merge_buf(buf, ft_lstnew(arg, ft_strlen(arg) + 1));
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

/*
** Uses to printf alias from alias array or to print error if isn't such alias
*/

int		btin_alias_print_one(char *arg)
{
	char	*ans;
	char	*tmp;

	tmp = NULL;
	ans = NULL;
	if (btin_alias_init(&arg, &ans, ASSIGN) != OUT)
	{
		tmp = btin_alias_line_form(ans);
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

/*
** Uses to save buffer to alias array after jobs from string were done
*/

int		btin_alias_merge_buf(t_list **arr, t_list *buf)
{
	t_list	*dest;

	if (buf)
	{
		dest = *arr;
		while (dest)
		{
			if (btin_alias_check_name(dest, buf))
			{
				free(dest->content);
				dest->content = buf->content;
				dest->content_size = buf->content_size;
				buf->content = NULL;
			}
			dest = dest->next;
		}
		if (buf->content)
			ft_lstadd(arr, ft_lstnew(buf->content, buf->content_size));
		free(buf->content);
		ft_lstfree_current(&buf);
	}
	return (0);
}

int		check_if_aliased(char *name)
{
	char	*ans;

	ans = NULL;
	if (name == NULL || name[0] == '\0')
		return (0);
	if (btin_alias_init(&name, &ans, ASSIGN) != OUT)
	{
		free(ans);
		return (ARG_ALIAS);
	}
	return (0);
}
