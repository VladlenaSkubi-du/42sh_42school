/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 14:41:31 by rbednar           #+#    #+#             */
/*   Updated: 2020/08/05 20:17:02 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

int		btin_alias_valid_name(char *name)
{
	int	i;

	i = (name) ? ft_strlen(name) - 1 : 0;
	while(i >= 0 && name[i])
	{
		if (ft_isalnum(name[i]) || name[i] == '!' || name[i] == '%' ||
			name[i] == ',' || name[i] == '@' || name[i] == '_')
			i--;
		else
			break ;	
	}
	if (++i == 0 && name)
		return (1);
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

char	*btin_alias_line_form(char *arg)
{
	char	*tmp;

	tmp = ft_xmalloc(sizeof(char) * (ft_strlen(arg) + 3));
	ft_strncat(tmp, arg, ft_strchri(arg, '='));
	ft_strcat(tmp, "='");
	ft_strcat(tmp, &arg[ft_strlen(tmp) - 1]);
	ft_strcat(tmp, "'");
	return (tmp);
}

int		btin_alias_check_name(t_list *arr, t_list *buf)
{
	char	*als;
	char	*tmp;
	int		ret;

	als = ft_strndup((char*)arr->content, ft_strchri((char*)arr->content, '='));
	tmp = ft_strndup((char*)buf->content, ft_strchri((char*)buf->content, '='));
	ret = ft_strcmp(als, tmp);
	free(als);
	free(tmp);
	return ( ret == 0 ? 1 : 0);	
}
