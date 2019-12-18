/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshawand <hshawand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 15:02:58 by hshawand          #+#    #+#             */
/*   Updated: 2019/12/18 16:21:24 by hshawand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	char	*tech;

	if (argc != 2)
		return (0);
	int len = ft_strlen(argv[1]);
	tech = ft_get_techline(argv[1]);
	while (len)
	{
		printf("\'%c\'=%03d\n", *argv[1], *tech);
		tech++;
		argv[1]++;
		len--;
	}
	(void)argc;
	free(tech);
	return (0);
}