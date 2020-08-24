/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 18:01:53 by kfalia-f          #+#    #+#             */
/*   Updated: 2020/08/24 16:39:07 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>
#include <builtin42.h>

int		export_error(char **tmp, int i)
{
	char *error;

	error = ft_strjoin("export: ", *tmp);
	error_handler(VARIABLE_ERROR | (ERR_RDONLY << 9), error);
	free(error);
	g_envi[i][0] |= ENV_VIS;
	free(*tmp);
	return (BTIN_ERROR);
}
