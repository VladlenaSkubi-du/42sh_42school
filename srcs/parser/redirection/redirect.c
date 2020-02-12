/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 13:46:57 by rbednar           #+#    #+#             */
/*   Updated: 2020/02/12 16:51:21 by rbednar          ###   ########.fr       */
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

int			ft_error_redir(t_ltree *final, size_t i)
{	
	if (i < final->end)
		error_handler((SYNTAX_ERROR | (ERR_REDIR << 9)),
		g_sign[(int)g_techline.line[i]]);
	else if (final->end != g_techline.len)
		error_handler((SYNTAX_ERROR | (ERR_REDIR << 9)),
		g_sign[(int)g_techline.line[final->end]]);
	else
		error_handler((SYNTAX_ERROR | (ERR_REDIR << 9)),
		"newline");
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
		if ((ret = ft_redir_gthen(final, &i)) == OUT)
			break ;
		i++;
	}
	return (ret);
}

/*
** Function to detect WORD of filename where/to need to redirect
*/

char		*ft_word_to_redir(size_t *i, t_ltree *final) //Correct
{
	char		*file;
	long long	size;
	size_t		start;

	size = 0;
	while (*i < final->end && g_techline.line[*i] == SPACE)
		(*i)++;
	start = *i;
	while (*i < final->end && g_techline.line[*i] == 0)
		size++ && (*i)++;
	if (size == 0)
		size = -1;
	file = ft_strndup(&g_cmd[start], size);
	ft_null_redir(start, size);
	return (file);
}
