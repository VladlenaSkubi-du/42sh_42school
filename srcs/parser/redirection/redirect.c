/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 13:46:57 by rbednar           #+#    #+#             */
/*   Updated: 2020/03/02 16:17:50 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

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

int			ft_error_redir(t_ltree *final)
{
	if ((final->flags >> 16 & 0x1FFF) == ERR_NO_ACC)
		error_handler((SYNTAX_ERROR | (ERR_NO_ACC << 9)), final->err);
	else if ((final->flags >> 16 & 0x1FFF) == ERR_BAD_FD)
		error_handler((SYNTAX_ERROR | (ERR_BAD_FD << 9)), final->err);
	else if ((final->flags >> 16 & 0x1FFF) == ERR_NO_FILE)
		error_handler((SYNTAX_ERROR | (ERR_NO_FILE << 9)), final->err);
	else if ((final->flags >> 16 & 0x1FFF) & ERR_REDIR)
	{
		final->err = ft_find_token_sep(&final->l_cmd[final->err_i]);
		final->err == NULL ? final->err = ft_strdup(final->token) : 0;
		if (final->err_i <= final->end)
			error_handler((SYNTAX_ERROR | (ERR_REDIR << 9)), final->err);
		else if (final->l_tline.line[final->end] == END_T)
			error_handler((SYNTAX_ERROR | (ERR_REDIR << 9)), "newline");
	}
	free(final->err);
	final->err = NULL;
	return (0);
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
	while (i <= final->end)
	{
		if ((ret = ft_redir_great(final, &i)) != 0)
			break ;
		if ((ret = ft_redir_dgreat(final, &i)) != 0)
			break ;
		if ((ret = ft_redir_greatand(final, &i)) != 0)
			break ;
		if ((ret = ft_redir_less(final, &i)) != 0)
			break ;
		if ((ret = ft_redir_dless(final, &i)) != 0)
			break ;
		if ((ret = ft_redir_lessand(final, &i)) != 0)
			break ;
		i++;
	}
	final->err_i = i;
	return (ret);
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
		while (*i < final->end && final->l_tline.line[*i] == SPACE)
			(*i)++;
		start = *i;
		while (*i < final->end && final->l_tline.line[*i] == WORD_P)
			size++ && (*i)++;
	}
	else if (rew_ff == REW)
		ft_word_to_redir_rew(i, final, &size, &start);
	if (size == 0)
		size = -1;
	file = ft_strndup(&final->l_cmd[start], size);
	ft_null_redir(start, size);
	return (file);
}

int			ft_word_to_redir_rew(size_t *i, t_ltree *final,
			long long *size, size_t *start)
{
	while (*i >= final->start && final->l_tline.line[*i] == WORD_P)
	{
		if (!(ft_isdigit(final->l_cmd[*i])))
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
