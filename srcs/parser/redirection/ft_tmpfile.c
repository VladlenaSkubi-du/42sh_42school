/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tmpfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:51:25 by rbednar           #+#    #+#             */
/*   Updated: 2020/08/05 13:41:31 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

static const char	g_letters[] =
"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

static int	ft_init_tmp(int *len, int *fd, int *try, char *tmpl)
{
	*len = ft_strlen(tmpl);
	*fd = -1;
	*try = -1;
	if (*len < L_TMPNAM || ft_strcmp(&tmpl[*len - 6], "XXXXXX"))
		return (-1);
	return (0);
}

static int	ft_try_create_fd(char **tmp, int *fd, int len, char **xxx)
{
	int		buf;

	buf = 0;
	*fd = open("/dev/random", O_RDONLY);
	while (++len < 6)
	{
		read(*fd, &buf, 1);
		(*xxx)[len] = g_letters[(buf + 300) % 62];
	}
	close(*fd);
	*fd = open(*tmp, O_RDWR | O_CREAT | O_EXCL | O_CLOEXEC, 0666);
	return (*fd);
}

static char	*add_slash(char **tmp, char *input, char *tmpl)
{
	if (input[ft_strlen(input) - 1] != '/')
		*tmp = ft_strjoin(input, "/");
	else
		*tmp = ft_strdup(input);
	*tmp = ft_strrejoin(*tmp, tmpl);
	return (*tmp);
}

/*
** Generate a temporary file name based on TMPL.  TMPL must match the
** rules for mk[s]temp (i.e. end in "XXXXXX").  The name constructed
** does not exist at the time of the call to mkstemp. TMPL is
** overwritten with the result. Implementation of mkstemp by POSIX,
** but it removes tmp file after usage like tmpfile()
** It recived *fd and try to create tmpfile TRY_SIZE times,
** if this does not work, returns -1
*/

int			ft_tmpfile(char *tmpl, int *fd)
{
	int		len;
	char	*tmp;
	int		try;
	char	*xxx;

	if (ft_init_tmp(&len, fd, &try, tmpl) == -1)
		return (-1);
	if (P_TMPDIR)
		tmp = add_slash(&tmp, P_TMPDIR, tmpl);
	xxx = (tmp != NULL) ? &tmp[len - 6] : NULL;
	while (*fd < 0)
	{
		len = -1;
		ft_try_create_fd(&tmp, fd, len, &xxx);
		if (++try > TMPFILE_TRY_SIZE)
			break ;
	}
	unlink(tmp);
	free(tmp);
	return (*fd);
}
