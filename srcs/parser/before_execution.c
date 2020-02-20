/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 19:35:23 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/20 17:37:24 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

/*
** Here we come with the counters of the beginning and the end of the 
** final processes and all the fds defined after redirection block
** Flags are defined also before in the parser block. Here we finish the
** preparation by forming the environ array for execution, forming 
** argc and argv variables
*/

int		before_exec(t_ltree *sub)
{
	// char		*add = NULL;
	
	// sub->envir = init_exec_environ();
	// add_new_to_exec_env(&sub->envir, add);
	argv_forming(sub);
	return (0);
}

int		argv_forming(t_ltree *sub)
{
	t_word	word;
	int		i;
	int		p;
	int		count;

	p = sub->start;
	sub->ar_c = ft_count_words(&(g_techline.line[sub->start]), SPACE,
				sub->end - sub->start + 1);
	sub->ar_v = (char **)ft_xmalloc(sizeof(char *) * (sub->ar_c + 1));
	i = 0;
	count = 0;
	while (count < sub->ar_c)
	{
		word = ft_give_me_word(&(g_techline.line[p]), SPACE, sub->end - p);
		word.start += p;
		(sub->ar_v)[i] = (char *)ft_xmalloc(sizeof(char) * (word.len + 1));
		ft_memcpy((sub->ar_v)[i], g_cmd + word.start, word.len);
		p = word.start + word.len;
		i++;
		count++;
	}
	sub->ar_v[sub->ar_c] = NULL;
	return (0);
}

t_word	ft_give_me_word(char const *s, char c, size_t len)
{
	t_word	k;
	size_t	i;
	size_t	l;

	i = 0;
	while (s[i] == c)
		i++;
	k.start = i;
	l = 0;
	while (s[i] != c && i < len)
	{
		l++;
		i++;
	}
	k.len = l;
	return (k);
}
