/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_home_from_etcpasswd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 14:16:49 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/26 14:18:02 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

char		*ft_home_from_etcpasswd(void)
{
	int		li;
	int		sy;
	int		fd;
	char	*line;
	char	**info;

	if ((li = find_in_variable(&sy, "UID")) < 0)
		return (NULL);
	fd = open("/etc/passwd", O_RDONLY);
	if (fd < 0)
		return (NULL);
	while (ft_gnl(fd, &line) > 0)
	{
		info = ft_strsplit(line, ':');
		free(line);
		if (ft_strcmp(info[2], &g_envi[li][sy]) == 0)
		{
			line = ft_strdup(info[5]);
			ft_arrdel(info);
			return (line);
		}
	}
	ft_arrdel(info);
	close(fd);
	return (NULL);
}
