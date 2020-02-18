/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 20:45:01 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/18 16:53:24 by sschmele         ###   ########.fr       */
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