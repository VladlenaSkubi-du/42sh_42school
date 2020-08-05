/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 14:41:31 by rbednar           #+#    #+#             */
/*   Updated: 2020/08/05 15:15:54 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

int		btin_alias_valid_name(char *name)
{
	int	i;

	i = (name) ? ft_strlen(name) - 1 : 0;
	while(i > 0 && name[i])
	{
		if (ft_isalnum(name[i]) || name[i] == '!' || name[i] == '%' ||
			name[i] == ',' || name[i] == '@' || name[i] == '_')
			i++;
		else
			break ;	
	}
	if (i == 0 && name)
		return (1);
	return (0);
}
