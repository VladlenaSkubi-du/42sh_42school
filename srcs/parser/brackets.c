/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:57:58 by rbednar           #+#    #+#             */
/*   Updated: 2020/01/30 12:11:39 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

static	int	ft_check(char str)
{
	if (str == 7)
		return (1);
	if (str == 8)
		return (4);
	if (str == 9)
		return (2);
	if (str == 10)
		return (5);
	if (str == 11)
		return (3);
	if (str == 12)
		return (6);
	return (0);
}

/*
** Function to check if all types of brackets are correctly closed
*/

int			ft_brackets(char *str, int end)
{
	long int	i;
	long int	buf;

	i = 0;
	while (str[i])
	{
		if (ft_check(str[i]) > 0 && ft_check(str[i]) < 4)
		{
			if ((buf = ft_brackets(&str[i + 1], ft_check(str[i]))) == -1)
				return (-1);
			else
				i += buf + 2;
		}
		if (ft_check(str[i]) >= 4 && ft_check(str[i]) <= 6)
		{
			if ((end + 3) != ft_check(str[i]))
				return (-1);
			else
				return (i);
		}
		i++;
	}
	if (end != 0)
		return (-1);
	return (0);
}
