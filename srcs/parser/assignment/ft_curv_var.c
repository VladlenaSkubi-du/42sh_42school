/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_curv_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 12:55:34 by rbednar           #+#    #+#             */
/*   Updated: 2020/03/03 01:58:52 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

/*
** Function finds and substitudes vars of type "${parameter}"
*/

int		ft_find_curv_var(t_ltree *sub)
{
	size_t	i;
	size_t	size;
	char	*find;

	i = -1;
	while (++i < sub->l_tline.len)
	{
		if (sub->l_tline.line[i] == DOLLAR && sub->l_tline.line[i + 1] == OBRACE)
		{
			size = 2;
			while (i + size < sub->end && sub->l_tline.line[i + size] != CBRACE)
				size++;
			find = ft_strndup(&sub->l_cmd[i + 2], size - 2);
			ft_type_param_check(sub, &find, &i);
		}
	}
	return (0);
}

/*
** Function finds and check subfunction of type "${parameter}"
** ${parameter:-word} and ${parameter-word}
** ${parameter:=word} and ${parameter=word}
** ${parameter:?word} and ${parameter?word}
** ${parameter:+word} and ${parameter+word}
** substring processing
** ${#parameter}
** ${parameter%[word]} and ${parameter%%[word]}
** ${parameter#[word]} and ${parameter##[word]}
*/

int		ft_type_param_check(t_ltree *sub, char **find, size_t *i)
{
	char	*oper;
	
	if ((oper = ft_strstr(*find, "-")))
		ft_param_colon_dash(sub, *find, oper, i);
	else if ((oper = ft_strstr(*find, "=")))
		ft_param_colon_equal(sub, *find, oper, i);
	else if ((oper = ft_strstr(*find, "?")))
		ft_param_colon_qmark(sub, *find, oper, i);
	else if ((oper = ft_strstr(*find, "+")))
		ft_param_colon_plus(sub, *find, oper, i);
	else if ((oper = ft_strstr(*find, "#")))
	{
		if (oper == *find)
			ft_substring_len(sub, *find, oper, i);
		else
			ft_substring_s_l_prefix(sub, *find, oper, i);
	}
	else if ((oper = ft_strstr(*find, "%")))
		ft_substring_s_l_suffix(sub, *find, oper, i);
	else
		ft_param_empty(sub, find, i);
	return (0);	
}

/*
** Function finds and substitudes classic vars of types
** ${parameter:-[word]} and ${parameter-[word]}
*/

int		ft_param_colon_dash(t_ltree *sub, char *find, char *oper, size_t *i)
{
	int		colon;
	
	colon = (*(oper - 1) == ':') ? 1 : 0;
	
	
	return (0);
}

/*
** Function finds and substitudes classic vars of types
** ${parameter:=[word]} and ${parameter=[word]}
*/

int		ft_param_colon_equal(t_ltree *sub, char *find, char *oper, size_t *i)
{
	int		colon;
	
	colon = (*(oper - 1) == ':') ? 1 : 0;
	
	
	return (0);
}

/*
** Function finds and substitudes classic vars of types
** ${parameter:?[word]} and ${parameter?[word]}
*/

int		ft_param_colon_qmark(t_ltree *sub, char *find, char *oper, size_t *i)
{
	int		colon;
	
	colon = (*(oper - 1) == ':') ? 1 : 0;
	
	
	return (0);
}

/*
** Function finds and substitudes classic vars of types
** ${parameter:?[word]} and ${parameter?[word]}
*/

int		ft_param_colon_plus(t_ltree *sub, char *find, char *oper, size_t *i)
{
	int		colon;
	
	colon = (*(oper - 1) == ':') ? 1 : 0;
	
	
	return (0);
}
