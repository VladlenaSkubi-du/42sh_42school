/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_values.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 16:27:15 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/26 10:33:17 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "hash.h"

static void		**g_hashtable_array;
static int		g_hashtable_array_size;
static int		g_hashtable_array_filled;
static int		g_hashtable_array_limit;

int				hashtable_init(void)
{
	g_hashtable_array_size = HASHTABLE_LENGTH;
	g_hashtable_array = (void**)ft_xmalloc(sizeof(void*) *
		(g_hashtable_array_size + 1));
	g_hashtable_array_filled = 0;
	g_hashtable_array_limit = g_hashtable_array_size / 2 +
		(g_hashtable_array_size / 2 / 2);
	return (0);
}

void			**get_hashtable_value(int *size)
{
	*size = g_hashtable_array_size;
	return (g_hashtable_array);
}

int				get_hashtable_filled(void)
{
	return (g_hashtable_array_filled);
}

int				change_hashtable_filled_value(int times)
{
	g_hashtable_array_filled += times;
	if (times == 0 || g_hashtable_array_filled < 0)
	{
		g_hashtable_array_filled = 0;
		return (0);
	}
	if (times > 0)
	{
		if (g_hashtable_array_filled / g_hashtable_array_size < 1 &&
				g_hashtable_array_filled >= g_hashtable_array_limit)
		{
			g_hashtable_array = ft_memrealloc_array(&g_hashtable_array,
				g_hashtable_array_size + 1,
				g_hashtable_array_size * 2 + 1);
			g_hashtable_array_size = g_hashtable_array_size * 2 + 1;
			g_hashtable_array_limit = g_hashtable_array_size / 2 +
				(g_hashtable_array_size / 2 / 2);
		}
	}
	return (0);
}
