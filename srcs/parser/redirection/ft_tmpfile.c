#include "shell42.h"
#include "parser.h"

#define TRY_SIZE 100

static const char	g_letters[] =
"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

static int  ft_init_tmp(int *len, int *fd, int *try, char *tmpl)
{
    *len = ft_strlen(tmpl);
	*fd = -1;
	*try = -1;
	if (*len < 6 || ft_strcmp(&tmpl[*len - 6], "XXXXXX"))
		return (-1);
    return (0);
}

static int  ft_try_create_fd(char **tmp, int *fd, int len, char **xxx)
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

/*
** Generate a temporary file name based on TMPL.  TMPL must match the
** rules for mk[s]temp (i.e. end in "XXXXXX").  The name constructed
** does not exist at the time of the call to mkstemp. TMPL is
** overwritten with the result. Implementation of mkstemp by POSIX,
** but it removes tmp file after usage like tmpfile()
** It recived *fd and try to create tmpfile TRY_SIZE times,
** if this does not work, returns -1
*/

int		    ft_tmpfile(char *tmpl, int *fd)
{
	int		len;
	char	*tmp;
	int		try;
	char	*xxx;

	if (ft_init_tmp(&len, fd, &try, tmpl) == -1)
        return (-1);
	xxx = (tmp = ft_strdup(tmpl)) != NULL ? &tmp[len - 6] : NULL;
	while (*fd < 0)
	{
		len = -1;
		ft_try_create_fd(&tmp, fd, len, &xxx);
		if (++try > TRY_SIZE)
			break ;
	}
	unlink(tmp);
	free(tmp);
	return (*fd);
}
