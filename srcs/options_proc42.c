/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_proc42.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 16:13:57 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/12 20:29:06 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

#define ERR_OPTION			-1
#define CONTINUE			0
#define STOP				1
#define NUM_OPTION			2
#define SUBOPTION			3
#define OPTION_FOUND		4
#define SUBOPTION_STARTS	16

/*
** @flag that comes to a function means that numbers can stay in the function
** after "-" (eg. fc-builtin). If @flag == 0 and there is a number after "-"
** it is considered as an error
** Because of the norm we had to put this flag in the end of the "final" that
** the function returns
**
** So the @final will be:
** 0000 0000 0000 0000
** 0000 0000 0000 0000
** 0000 0000 0000 0000 - sector for "suboptions" with "--"
** 0000 0000 0000 0001 - anyway because of the flag, here bits where "options"
** will be activated
**
** Example:
** If @flags_arr[3]{"erlns", "--help", "--usage"} and
** @arr {"fc, "-r", "1", "10", "--help" "--" "--usage"}
**
** @final will be:
** 0000 0000 0000 0000
** 0000 0000 0000 0000
** 0000 0000 0000 0001 - "help" activated
** 0000 0000 0000 0101 - "r" and "numbers" activated
** usage is not activated because after "--" everything is regarded as arguments
*/

int			find_options(int num, char *flags_arr[num], char **arr, int flag)
{
	int     i;
	int		final;
	int		res;

	i = 0;
	final = 0;
	if (flag == 1)
		final |= 0x1;
	while (arr[++i])
	{
		if (arr[i][0] != '-')
			continue;
		res = options_in_arg(arr[i], num, flags_arr, &final);
		if (res == ERR_OPTION)
		{
			error_handler(OPTIONS_REQUIRED | (ERR_BTIN_INVALID << 9), arr[0]);
			return (ERR_OPTION);
		}
		else if (res == STOP)
			break ;
	}
	return (final);
}

/*
** Accepts argument after the valid flag as GNU lib does
*/

int			options_in_arg(char *arri, int num, char *flags_arr[num], int *final)
{
	int     j;
	int		res;
	int		tmp;
	
	j = 0;
	tmp = -1;
	while (arri[++j])
	{
		res = options_proc(arri[j], flags_arr[0], final);
		if (res == ERR_OPTION)
			return ((tmp != CONTINUE) ? ERR_OPTION : CONTINUE);
		else if (res == NUM_OPTION && !(tmp == -1 || tmp == NUM_OPTION))
			return (ERR_OPTION);
		else if (res == SUBOPTION)
		{
			res = suboptions_proc(arri, num, flags_arr, final);
			if (res == STOP)
				return (STOP);
			else if (res == ERR_OPTION)
				return (ERR_OPTION);
			return (CONTINUE);
		}
		tmp = res;
	}
	return (CONTINUE);
}

/*
** First we form a mask for the final int and after "activate" the bit
*/

int			options_proc(char arrij, char *flags_arr, int *final)
{
	int		k;
	size_t	len;
	int		mask;

	k = -1;
	len = ft_strlen(flags_arr) + 1;
	mask = 1;
	if (arrij == '-')
		return (SUBOPTION);
	if ((*final & 0x1) && (arrij >= '0' && arrij <= '9'))
		return (NUM_OPTION);
	else if (!(*final & 0x1) && (arrij >= '0' && arrij <= '9'))
		return (ERR_OPTION);
	else if (ft_isalpha(arrij) == 0)
		return (ERR_OPTION);
	while (flags_arr[++k])
	{
		if (arrij == flags_arr[k])
		{
			mask = mask << (len - k - 1);
			*final |= mask;
			return (CONTINUE);
		}
	}
	return (ERR_OPTION);
}

int			suboptions_proc(char *arri, int num, char *flags_arr[num], int *final)
{
	size_t	len;
	size_t	len_arg;
	int		mask;
	int		i;
	
	if (arri[2] == '\0')
		return (STOP);
	len = SUBOPTION_STARTS;
	len_arg = ft_strlen(arri);
	mask = 1;
	i = 0;
	while (++i < num)
	{
		if (ft_strdiff(arri, flags_arr[i]) == 1)
		{
			len += i - 1;
			mask = mask << len;
			*final |= mask;
			return (CONTINUE);
		}
	}
	return (ERR_OPTION);
}