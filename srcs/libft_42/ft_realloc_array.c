/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 20:45:01 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/19 12:36:36 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "libft_42.h"

char				**ft_realloc_array(char ***subj, int len_subj,
						int len_needed)
{
	int				i;
	char			**new;
	char			**old;

	i = 0;
	old = *subj;
	new = (char**)ft_xmalloc(sizeof(char*) * (len_needed + 1));
	while (old[i])
	{
		new[i] = ft_strdup(old[i]);
		i++;
	}
	ft_arrdel(old);
	return (new);
}
