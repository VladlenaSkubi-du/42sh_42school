/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parser_processing.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 16:45:09 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/21 16:45:10 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

void		print_techline(char *cmd, char *techline, int len_tech)
{
	int	i;

	i = -1;
	ft_printf("g_cmd = %s\n", cmd);
	ft_printf("techline cur:");
	while (++i <= len_tech)
		ft_printf("%3d", techline[i]);
	ft_printf("\n");
}
