/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 17:07:15 by rbednar           #+#    #+#             */
/*   Updated: 2020/08/07 20:29:40 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

int		btin_alias_copy_buf(t_list **alias, t_list **buf)
{
	t_list *tmp;

	tmp = *buf;
	ft_lstclear(alias);
	while (tmp)
	{
		ft_lstadd(alias, ft_lstnew(tmp->content, tmp->content_size));
		tmp = tmp->next;
	}
	return (0);
}
