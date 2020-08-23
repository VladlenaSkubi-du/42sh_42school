/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_help_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 16:02:12 by rbednar           #+#    #+#             */
/*   Updated: 2020/08/23 20:19:42 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

int		ft_param_word_sub(t_ltree *sub, char **line, char *oper, int *i)
{
	char *buf;

	buf = ft_parsing_str(oper + 1);
	ft_reglue(i, ft_strlen(*line) + 2, sub);
	insert_str_in_loc_strs(sub, &buf, i, TEXT);
	return (0);
}

/*
** Exept ft_lst_ltree_clear this function clear one element of t_ltree *tree
*/

void	ft_one_ltree_clear(t_ltree *buf)
{
	t_list		*tmp;

	if (buf)
	{
		free(buf->l_cmd);
		free(buf->l_tline.line);
		ft_arrdel(buf->envir);
		ft_arrdel(buf->ar_v);
		if ((tmp = buf->fd))
			while (tmp)
			{
				free(((t_fd_redir *)(tmp->content))->name);
				tmp = tmp->next;
			}
		ft_lstclear(&buf->fd);
		free(buf->err);
		free(buf->token);
		free(buf);
	}
}

int		ft_param_error_msg(t_ltree *sub, char **find, char *oper)
{
	int		len;
	char	*buf;
	size_t	j;

	ft_colon_check(&len, find, &oper, &j);
	*oper = '\0';
	sub->err = ft_strdup(*find);
	if (oper[1] == '\0')
		sub->err_i |= ERR_OUT | VARIABLE_ERROR | ERR_UNSET << 9;
	else
	{
		sub->err_i |= ERR_OUT | VARIABLE_ERROR | ERR_SET << 9;
		sub->err = ft_strrejoin(sub->err, ": ");
		buf = ft_parsing_str(oper + 1);
		sub->err = ft_strrejoin(sub->err, buf);
		free(buf);
	}
	return (sub->err_i);
}

char	*ft_parsing_str(char *str)
{
	t_ltree *buf;
	char	*ret;

	ret = NULL;
	if (str)
	{
		buf = (t_ltree *)ft_xmalloc(sizeof(t_ltree));
		ltree_init(buf);
		buf->l_cmd = ft_strdup(str);
		ft_get_techline(buf->l_cmd, &buf->l_tline);
		buf->end = buf->l_tline.len;
		nullify(&buf->l_tline.line, buf->l_tline.len);
		pre_parsing_cut_glue(buf);
		ft_find_tilda(buf, ASSIGN);
		ft_substitution(buf);
		ret = buf->l_cmd;
		buf->l_cmd = NULL;
		ft_one_ltree_clear(buf);
	}
	return (ret);
}
