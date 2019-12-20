/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_functionalities.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:20:32 by sschmele          #+#    #+#             */
/*   Updated: 2019/11/14 15:01:44 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void			bell_sound(void)
{
	char		buf[10];
	char		*buffer;

	buffer = buf;
	tputs(tgetstr("bl", &buffer), 1, ft_putint);
	buffer = buf;
}
