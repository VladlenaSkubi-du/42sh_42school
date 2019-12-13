/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_usage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 15:53:06 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/13 15:53:14 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int				printc(int c)
{
	return (write(1, &c, 1));
}

int				putcap(char *cap) //наиболее используемые капы можно сохранить
{
	char		buff[20];
	char		*ptr;

	ptr = buff;
	tputs(tgetstr(cap, &ptr), 1, printc);
	ptr = buff;
	ft_bzero(ptr, 20);
	return (0);
}

int				position_cursor(char *cap, int x, int y)
{
	char		buff[20];
	char		*ptr;

	ptr = buff;
	tputs(tgoto(tgetstr(cap, &ptr), x, y), 1, printc);
	ptr = buff;
	ft_bzero(ptr, 20);
	return (0);
}
