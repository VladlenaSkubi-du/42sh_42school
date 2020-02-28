/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 22:26:57 by rbednar           #+#    #+#             */
/*   Updated: 2020/02/28 21:37:32 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

int		ft_substitution(t_ltree *sub)
{
	ft_find_tilda(sub, LINE);
	// ft_find_var(sub);
	// ft_find_curv_var(sub);
	// ft_find_sub_subshell(sub);
	// ft_find_globbing(sub);
	return (0);
}

/*
** It gets insert string and insert it to l_cmd and l_tline of sub
*/

int     insert_str_in_loc_strs(t_ltree *sub, char **insert, size_t *i, int flag)
{
	char	*buf;
	size_t	len_ins;
	
	len_ins = ft_strlen(*insert);
	buf = (char *)ft_xmalloc(sizeof(char) * (sub->l_tline.len + len_ins));
	ft_memcpy(buf, sub->l_cmd, *i);
	ft_memcpy(buf + *i, *insert, len_ins);
	ft_strcpy(buf + *i + len_ins, sub->l_cmd + *i + 1);
	free(sub->l_cmd);
	sub->l_cmd = buf;
	sub->l_tline.alloc_size += len_ins - 1;
	buf = (char *)ft_xmalloc(sizeof(char) * (sub->l_tline.alloc_size));
	ft_memcpy(buf, sub->l_tline.line, *i);
	sub->l_tline.len += len_ins - 1;
	len_ins += *i;
	while (*i < len_ins)
	{
		buf[*i] = (flag == TEXT) ? flag : get_tech_num(*insert[len_ins - *i]);
		(*i)++;
	}
	ft_strcpy(buf + *i, sub->l_tline.line + *i - ft_strlen(*insert) + 1);
	free(sub->l_tline.line);
	sub->l_tline.line = buf;
	free(*insert);
	return (0);
}

		// printf("techline pre:");//печать для проверки
		// *i = -1;
		// while (++*i < sub->l_tline.alloc_size - 1)
		// 	printf("%3d", sub->l_tline.line[*i]);
		// printf("\n");
		// printf("l_cmd pre=%s<end\n", sub->l_cmd);