/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 17:35:11 by kfalia-f          #+#    #+#             */
/*   Updated: 2020/08/21 16:09:58 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

int		ft_valid_cd(char **argv, int i)
{
	if (argv[i] && argv[i + 1])
	{
		ft_error_cd(NULL, 5);
		return (1);
	}
	return (0);
}
