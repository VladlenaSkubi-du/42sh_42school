/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_underline_inverse_video.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 20:00:40 by sschmele          #+#    #+#             */
/*   Updated: 2019/11/13 15:46:59 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void			underline_on(void)
{
	char		buf[10];
	char		*buffer;

	buffer = buf;
	tputs(tgetstr("us", &buffer), 1, ft_putint);
	buffer = buf;
}

void			underline_off(void)
{
	char		buf[10];
	char		*buffer;

	buffer = buf;
	tputs(tgetstr("ue", &buffer), 1, ft_putint);
	buffer = buf;
}

void			inverse_video_on(void)
{
	char		buf[10];
	char		*buffer;
	char		*inverse_video;

	buffer = buf;
	inverse_video = tgetstr("mr", &buffer);
	buffer = buf;
	tputs(inverse_video, 1, ft_putint);
}

void			inverse_video_off(void)
{
	char		buf[10];
	char		*buffer;
	char		*inverse_video;

	buffer = buf;
	inverse_video = tgetstr("me", &buffer);
	buffer = buf;
	tputs(inverse_video, 1, ft_putint);
}
