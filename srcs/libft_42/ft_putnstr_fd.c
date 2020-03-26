/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 22:09:42 by vladlenasku       #+#    #+#             */
/*   Updated: 2020/03/26 22:11:56 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "libft_42.h"

void				ft_putnstr_fd(char *str, int n, int fd)
{
	int				i;

	i = 0;
	while (i < n && str[i])
	{
		ft_putchar_fd(str[i], fd);
		i++;
	}
}