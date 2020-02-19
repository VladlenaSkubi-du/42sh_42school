/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_types_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:20:07 by rbednar           #+#    #+#             */
/*   Updated: 2020/02/19 19:26:51 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

static const char	g_letters[] =
"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

/*
** Function to detect "[n]< word"
*/

int		ft_redir_less(t_ltree *final, size_t *i)
{
	t_fd_redir	fd_open;
	char		*f_name;

	f_name = NULL;
	fd_open.type = IN_R;
	if (g_techline.line[*i] == LTHAN && (g_techline.line[*i + 1] != LTHAN &&
		(g_techline.line[*i + 1] != AND || g_techline.line[*i + 1] == PIPE)))
	{
		fd_open.fd_in = ft_check_n_redir_op(*i, final, STDIN_FILENO);
		ft_null_redir(*i, 1);
		(*i)++;
		if ((f_name = ft_word_to_redir(i, final, FF)) != NULL)
		{
			if ((fd_open.fd_out = open(f_name, O_RDONLY |
			O_CLOEXEC | O_SYNC | O_NOCTTY)) == -1)
				return (ft_access_check(&f_name, final, i, R_OK));
			else
				add_redir_fd(final, &fd_open);
		}
		else
			return (ft_error_redir(final, *i, ERR_REDIR, NULL));
	}
	free(f_name);
	return (0);
}

/*
** Function to detect "[n]<<stop_word" here-document
*/

int		ft_redir_dless(t_ltree *final, size_t *i)
{
	t_fd_redir	fd_open;
	char		*f_name;

	f_name = NULL;
	fd_open.type = IN_R;
	if (g_techline.line[*i] == LTHAN && g_techline.line[*i + 1] == LTHAN)
	{
		fd_open.fd_in = ft_check_n_redir_op(*i, final, STDIN_FILENO);
		ft_null_redir(*i, 2);
		(*i) += 2;
		if ((f_name = ft_word_to_redir(i, final, FF)) != NULL)
			return (ft_heredoc_form(&fd_open, f_name, final, i));
		else
			return (ft_error_redir(final, *i, ERR_REDIR, NULL));
	}
	free(f_name);
	return (0);
}

/*
** Function to detect "[n]<&[m]" (input from fd or file if)
*/

int		ft_redir_lessand(t_ltree *final, size_t *i)
{
	t_fd_redir	fd_open;
	char		*f_name;

	f_name = NULL;
	fd_open.type = IN_R;
	if (g_techline.line[*i] == LTHAN && (g_techline.line[*i + 1] == AND))
	{
		fd_open.fd_in = ft_check_n_redir_op(*i, final, STDIN_FILENO);
		ft_null_redir(*i, 2);
		(*i) += 2;
		if ((f_name = ft_word_to_redir(i, final, FF)) != NULL)
			return (ft_num_or_word_in(&f_name, &fd_open, i, final));
		else
			return (ft_error_redir(final, *i, ERR_REDIR, NULL));
	}
	free(f_name);
	return (0);
}

int		ft_heredoc_form(t_fd_redir *fd_open, char *f_name, t_ltree *final, size_t *i)
{
	if (g_prompt.prompt_func == main_prompt)
	{
		fd_open->fd_out = ft_tmpfile(TMPL);
		add_redir_fd(final, fd_open);
		g_heredoc.stop.stop_w = ft_strdup(f_name);
		g_heredoc.stop.fd = fd_open->fd_out;
		ft_add_list_to_end(&(g_heredoc.list),
			ft_lstnew(&g_heredoc.stop, sizeof(t_stop)));
	}
	return (0);
}

/*
** Generate a temporary file name based on TMPL.  TMPL must match the
** rules for mk[s]temp (i.e. end in "XXXXXX").  The name constructed
** does not exist at the time of the call to mkstemp.  TMPL is
** overwritten with the result. Implementation of mkstemp by POSIX
** NOT delete file when closed!!! NEED TO unlink() file
*/

int		ft_tmpfile(char *tmpl)
{
	int		len;
	char	*tmp;
	char	*xxx;
	int		fd;
	int		buf;

	len = ft_strlen(tmpl);
	fd = -1;
	if (len < 6 || ft_strcmp(&tmpl[len - 6], "XXXXXX"))
		return (-1);
	tmp = ft_strdup(tmpl);
	xxx = &tmp[len - 6];
	while (fd < 0)
	{
		len = -1;
		fd = open("/dev/random", O_RDONLY);
		while (++len < 6)
		{
			read(fd, &buf, 1);
			xxx[len] = g_letters[(buf + 77) % 62];
		}
		close(fd);
		fd = open(tmp, O_RDWR | O_CREAT | O_EXCL | O_CLOEXEC,
			S_IREAD | S_IWRITE);
	}
	unlink(tmp);
	return (fd);
}
