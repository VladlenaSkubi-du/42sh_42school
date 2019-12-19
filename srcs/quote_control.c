/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:28:46 by hshawand          #+#    #+#             */
/*   Updated: 2019/12/19 15:32:42 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		terminate(char mode, char *ptr)
{
	if (mode == 1)
	{
		if (*ptr == 1 || *ptr == 3 || *ptr == 4 || *ptr == 9 \
		|| *ptr == 10 || *ptr == 14 || *ptr == 15 || *ptr == 16 \
		|| *ptr == 17 || *ptr == 18)
			*ptr = 0;
	}
	else
		*ptr = 0;
	return (0);
}

int		nullify(void)
{
	char	*ptr;
	char	nullifier;
	size_t	count;

	count = 0;
	nullifier = 0;
	ptr = g_techline;
	while (count < g_cmd_size)
	{
		if (!nullifier)
		{
			if (*ptr == 5)
				nullifier = 1;
			else if (*ptr == 6)
				nullifier = 2;
		}
		else if ((nullifier == 1 && *ptr == 5) || (nullifier == 2 && *ptr == 6))
			nullifier = 0;
		else
			terminate(nullifier, ptr);
		ptr++;
		count++;
	}
	return (0);
}