/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 13:46:57 by rbednar           #+#    #+#             */
/*   Updated: 2020/02/19 19:28:51 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

static char	*g_sign[22] = {
	"\0", " ", "\\", ";", "&", "\"", "\'", "(", ")", "[", "]",
	"{", "}", "$", "~", "|", ">", "<", "*", "=", "\n", "#"};

/*
** Function to null NUM symbols in g_techline and g_cmd since "i" index
*/

int			ft_null_redir(size_t i, long long num)
{
	while (num > 0)
	{
		g_cmd[i] = ' ';
		g_techline.line[i] = SPACE;
		num--;
		i++;
	}
	return (0);
}

int			ft_error_redir(t_ltree *final, size_t i, int flag, char **str)
{
	ft_heredoc_rem();
	if (flag == ERR_NO_ACC)
		error_handler((SYNTAX_ERROR | (ERR_NO_ACC << 9)), *str);
	else if (flag == ERR_BAD_FD)
		error_handler((SYNTAX_ERROR | (ERR_BAD_FD << 9)), *str);
	else if (flag == ERR_NO_FILE)
		error_handler((SYNTAX_ERROR | (ERR_NO_FILE << 9)), *str);
	else if (flag == ERR_REDIR && i < final->end)
		error_handler((SYNTAX_ERROR | (ERR_REDIR << 9)),
		g_sign[(int)g_techline.line[i]]);
	else if (flag == ERR_REDIR && final->end != g_techline.len)
		error_handler((SYNTAX_ERROR | (ERR_REDIR << 9)),
		g_sign[(int)g_techline.line[final->end]]);
	else
		error_handler((SYNTAX_ERROR | (ERR_REDIR << 9)),
		"newline");
	(str && *str != NULL) ? free(*str) : 0;
	return (OUT);
}

/*
** Function to find redirections with grammer rules
*/

int			ft_find_redirection(t_ltree *final)
{
	size_t	i;
	int		ret;

	i = final->start;
	ret = 0;
	while (i < final->end)
	{
		if ((ret = ft_redir_great(final, &i)) == OUT)
			break ;
		if ((ret = ft_redir_dgreat(final, &i)) == OUT)
			break ;
		if ((ret = ft_redir_greatand(final, &i)) == OUT)
			break ;
		if ((ret = ft_redir_less(final, &i)) == OUT)
			break ;
		if ((ret = ft_redir_dless(final, &i)) == OUT)
			break ;
		if ((ret = ft_redir_lessand(final, &i)) == OUT)
			break ;
		i++;
	}
	return (ft_check_is_heredoc(ret));
}

/*
** Function to detect WORD of filename where/to need to redirect
*/

char		*ft_word_to_redir(size_t *i, t_ltree *final, int rew_ff)
{
	char		*file;
	long long	size;
	size_t		start;

	size = 0;
	start = 0;
	if (rew_ff == FF)
	{
		while (*i < final->end && g_techline.line[*i] == SPACE)
			(*i)++;
		start = *i;
		while (*i < final->end && g_techline.line[*i] == 0)
			size++ && (*i)++;
	}
	else if (rew_ff == REW)
		ft_word_to_redir_rew(i, final, &size, &start);
	if (size == 0)
		size = -1;
	file = ft_strndup(&g_cmd[start], size);
	ft_null_redir(start, size);
	return (file);
}

int			ft_word_to_redir_rew(size_t *i, t_ltree *final,
			long long *size, size_t *start)
{
	while (*i >= final->start && g_techline.line[*i] == 0)
	{
		if (!(ft_isdigit(g_cmd[*i])))
		{
			*size = -1;
			break ;
		}
		(*size)++ && (*i)--;
	}
	if (*size != -1)
	{
		if (*i == final->start)
			*start = *i;
		else
			*start = *i + 1;
	}
	return (0);
}
