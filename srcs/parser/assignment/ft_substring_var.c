/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substring_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 00:22:23 by rbednar           #+#    #+#             */
/*   Updated: 2020/03/03 17:21:44 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

/*
** Function finds and substitudes classic vars of type "${#parameter}"
*/

int		ft_substring_len(t_ltree *sub, char **line, char *oper, size_t *i)
{
	return (0);
}

/*
** Function finds and substitudes classic vars of types
** ${parameter#[word]} and ${parameter##[word]}
*/

int		ft_substring_s_l_prefix(t_ltree *sub, char **line, char *oper, size_t *i)
{
	int		s_l;
	
	s_l = (oper[1] == '#') ? LARGE : SMALL;
	
	
	return (0);
}

/*
** Function finds and substitudes classic vars of types
** ${parameter%[word]} and ${parameter%%[word]}
*/

int		ft_substring_s_l_suffix(t_ltree *sub, char **line, char *oper, size_t *i)
{
	int		s_l;
	
	s_l = (oper[1] == '%') ? LARGE : SMALL;
	
	return (0);
}

int		ft_param_word_sub(t_ltree *sub, char **line, char *oper, size_t *i)
{
	t_ltree *buf;
	
	buf = (t_ltree *)ft_xmalloc(sizeof(t_ltree));
	ltree_init(buf);
	buf->l_cmd = ft_strdup(oper + 1);
	ft_get_techline(buf->l_cmd, &buf->l_tline);
	buf->end = buf->l_tline.len;
	nullify(&buf->l_tline.line, buf->l_tline.len);
	pre_parsing_cut_glue(buf);
	ft_substitution(buf);
	ft_reglue(i, ft_strlen(*line) + 2, sub);
	free(*line);
	insert_str_in_loc_strs(sub, &buf->l_cmd, i, TEXT);
	buf->l_cmd = NULL;	
	ft_one_ltree_clear(buf);
	return (0);
}

/*
** Exept ft_lst_ltree_clear this function clear one element of t_ltree *tree
*/

void	ft_one_ltree_clear(t_ltree *buf)
{
	if (buf)
	{
		free(buf->l_cmd);
		free(buf->l_tline.line);
		ft_arrdel(buf->envir);
		ft_arrdel(buf->ar_v);
		ft_lstclear(&buf->fd);
		free(buf->err);
		free(buf->token);
		free(buf);
	}
	buf = NULL;
}