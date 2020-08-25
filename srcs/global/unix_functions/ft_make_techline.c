/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_techline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 16:44:38 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/25 22:23:25 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

/*
** Function to check if find char is in use or just text
*/

char		get_tech_num(char check)
{
	char	*base;
	int		i;

	base = " \\;&\"\'()[]{}$~|><*=\n#!:\t";
	i = 0;
	while (base[i])
	{
		if (base[i] == check)
		{
			if (i == 24)
				return (2);
			else
				return (i + 2);
		}
		i++;
	}
	if (check == EOF)
		return (EOF);
	return (1);
}

char		*ft_make_techline(char *cmd, int len)
{
	int		i;
	char	*techline;

	i = 0;
	if (cmd == NULL || cmd[0] == 0)
	{
		techline = (char*)ft_xmalloc(2);
		techline[0] = END_T;
		return (techline);
	}
	techline = (char*)ft_xmalloc(len + 2);
	while (cmd[i])
	{
		techline[i] = get_tech_num(cmd[i]);
		i++;
	}
	techline[i] = END_T;
	return (techline);
}
