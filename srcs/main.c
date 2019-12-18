/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshawand <hshawand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 15:02:58 by hshawand          #+#    #+#             */
/*   Updated: 2019/12/18 18:13:29 by hshawand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	char	*to_free;

	if (argc != 2)
		return (0);
	parser(argv[1]);
	to_free = g_techline;
	while (g_cmd_size)
	{
		printf("\'%c\'=%03d\n", *argv[1], *g_techline);
		g_techline++;
		argv[1]++;
		g_cmd_size--;
	}
	(void)argc;
	free(to_free);
	return (0);
}