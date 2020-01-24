/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_usage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 15:53:06 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/24 13:31:50 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"
#define TERMCAP_SIZE 20

int				printc(int c)
{
	return (write(1, &c, 1));
}

/*static char	*left;
static char	*right;
static char	*up;
static char	*down;
static char	*cd_clear;
static char	*scroll;
static char	*absolute_line;
*/

int				putcap(char *cap) //TODO наиболее используемые капы сохранить
{
	char		buff[TERMCAP_SIZE];
	char		*ptr;

	ptr = buff;
	tputs(tgetstr(cap, &ptr), 1, printc);
	ptr = buff;
	ft_bzero(ptr, 20);
	return (0);
}

int				position_cursor(char *cap, int x, int y)
{
	char		buff[TERMCAP_SIZE];
	char		*ptr;

	ptr = buff;
	tputs(tgoto(tgetstr(cap, &ptr), x, y), 1, printc);
	ptr = buff;
	ft_bzero(ptr, 20);
	return (0);
}
