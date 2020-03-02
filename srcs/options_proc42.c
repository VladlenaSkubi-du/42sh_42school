/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_proc42.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 16:13:57 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/02 20:03:55 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

int			find_options(char *flags_arr, char **arr, int flag, char *prog)
{
	int     i;
	int     j;
	int		final;
	int		tmp;

	i = -1;
	j = 0;
	final = 0;
	while (arr[++i])
	{
		if (arr[i][0] != '-')
			continue;
		while (arr[i][++j])
		{
			if ((tmp = options_proc(arr[i][j], flags_arr, flag, &final)) == -1)
			{
				printf("%d\n", final);
				return (final);
			}
			else if (tmp == -2)
			{
				error_handler(OPTIONS_REQUIRED | (ERR_BUILTIN << 9), prog);
				return (0);
			}
		}
		j = 0;
	}
	printf("%d\n", final);
	return (0);
}

/*
** First we form a mask for the final int and after "activate" the bit
*/

int			options_proc(char arrij, char *flags_arr, int flag, int *final)
{
	int		k;
	size_t	len;
	int		mask;

	k = -1;
	len = ft_strlen(flags_arr);
	mask = 1;
	if (arrij == '-')
		return (-1);
	if (flag == 1 && (arrij >= 0 && arrij <= 9))
		return (0);
	else if (flag == 0 && (arrij >= 0 && arrij <= 9))
		return (-2);
	while (flags_arr[++k])
	{
		if (arrij == flags_arr[k])
		{
			mask = mask << (len - k - 1);
			*final |= mask;
		}
	}
	return (0);
}