/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:02:53 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/03 19:17:55 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

#define         MAXDIR 100

int             start_history(void)
{
	char        dir[MAXDIR];
	int         fd;

	init_history();
	ft_bzero(dir, MAXDIR);
	getcwd(dir, MAXDIR);
	if (dir[0] == 0)
		return (0);
	ft_strcat(dir, "/.42sh_history");
	fd = open(dir, O_RDONLY);
	if (fd == -1)
		return (0);
	// while (get_next_line(fd, ))
	return (0);
}

void            init_history(void)
{
	size_t		i;
	int			tmp;

	i = 0;
	while (ft_strncmp(g_shvar[i], "HISTFILESIZE=",
		(tmp = ft_strchri(g_shvar[i], '=') + 1)) != 0)
		i++;
	g_hist.len = ft_atoi(&g_shvar[i][tmp]);
	g_hist.hist = (char**)ft_xmalloc(sizeof(char*) * (g_hist.len + 1));
	g_hist.hist[g_hist.len] = 0;
	g_hist.last = 0;
	g_hist.start = 0;
}