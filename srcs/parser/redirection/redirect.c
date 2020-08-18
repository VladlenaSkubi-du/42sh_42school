/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:55:32 by rbednar           #+#    #+#             */
/*   Updated: 2020/08/18 21:45:00 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

/*
** Function to null NUM symbols in g_techline and g_cmd since "i" index
*/

int			ft_null_redir(t_ltree *pos, size_t i, long long num)
{
	while (num > 0)
	{
		pos->l_cmd[i] = ' ';
		pos->l_tline.line[i] = SPACE;
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
		if (final->err_i < (size_t)final->end ||
			(final->err_i == (size_t)final->end &&
			final->l_tline.line[final->end] != END_T))
			error_handler((SYNTAX_ERROR | (ERR_REDIR << 9)), final->err);
		else if (final->l_tline.line[final->end] == END_T)
			error_handler((SYNTAX_ERROR | (ERR_REDIR << 9)), "newline");
	}
	return (0);
}

/*
** Function to find redirections with grammer rules
*/

int			ft_find_redirection_check(t_ltree *final, int *i)
{
	int		ret;

	ret = 0;
	if ((ret = ft_redir_great_check(final, i)) != 0)
		return (ret);
	if ((ret = ft_redir_dgreat_check(final, i)) != 0)
		return (ret);
	if ((ret = ft_redir_greatand_check(final, i)) != 0)
		return (ret);
	if ((ret = ft_redir_less_check(final, i)) != 0)
		return (ret);
	if ((ret = ft_redir_dless(final, i)) != 0)
		return (ret);
	if ((ret = ft_redir_dless_min(final, i)) != 0)
		return (ret);
	if ((ret = ft_redir_lessand_check(final, i)) != 0)
		return (ret);
	return (ret);
}

/*
** Function to detect WORD of filename where/to need to redirect
*/

char		*ft_word_to_redir(int *i, t_ltree *final, int rew_ff)
{
	char		*file;
	char		*buf;
	long long	size;
	size_t		start;

	size = 0;
	start = 0;
	if (rew_ff == FF || rew_ff == HERE)
	{
		while (*i < final->end && final->l_tline.line[*i] == SPACE)
			(*i)++;
		start = *i;
		while (*i < final->end && final->l_tline.line[*i] != SPACE && (*i)++)
			size++;
	}
	else if (rew_ff == REW)
		ft_word_to_redir_rew(i, final, &size, &start);
	if (size == 0)
		size = -1;
	buf = ft_strndup(&final->l_cmd[start], size);
	file = (rew_ff == FF) ? ft_parsing_str(buf) : buf;
	(rew_ff == FF) ? free(buf) : 0;
	ft_null_redir(final, start, size);
	return (file);
}

int			ft_word_to_redir_rew(int *i, t_ltree *final,
			long long *size, size_t *start)
{
	if (*i > 0)
		*i -= 1;
	while (*i >= final->start && final->l_tline.line[*i] == WORD_P)
	{
		if (!(ft_isdigit(final->l_cmd[*i])))
		{
			*size = -1;
			break ;
		}
		(*size)++;
		(*i)--;
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
