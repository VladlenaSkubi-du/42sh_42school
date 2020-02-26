/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 19:35:23 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/26 17:29:51 by rbednar          ###   ########.fr       */
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

int		before_exec(t_ltree *sub, t_ltree *block)
{
	char		*add = NULL;
	int			err;
	
	ft_local_copy_lines(sub);
	// ft_substitution(sub);
	sub->envir = init_exec_environ();
	// add_new_to_exec_env(&sub->envir, add);
	pre_parsing_cut_glue(sub);
	if ((err = ft_find_redirection(sub)) != 0)
	{
		sub->flags |= ERR_IN;
		sub->flags |= err << 16;
	}
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
	sub->ar_c = ft_count_words(&(sub->l_techline.line[0]), SPACE,
				sub->l_techline.len);
	sub->ar_v = (char **)ft_xmalloc(sizeof(char *) * (sub->ar_c + 1));
	i = 0;
	count = 0;
	while (count < sub->ar_c)
	{
		word = ft_give_me_word(&(sub->l_techline.line[p]), SPACE,
			sub->l_techline.len - p);
		word.start += p;
		(sub->ar_v)[i] = (char *)ft_xmalloc(sizeof(char) * (word.len + 1));
		ft_memcpy((sub->ar_v)[i], sub->l_cmd + word.start, word.len);
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

int		ft_local_copy_lines(t_ltree *sub)
{
	sub->l_cmd = ft_strndup(&g_cmd[sub->start], sub->end - sub->start);
	sub->l_techline.line = ft_strndup(&g_techline.line[sub->start],
		sub->end - sub->start + 1);
	sub->l_techline.len = sub->end - sub->start;
	sub->l_techline.alloc_size = sub->end - sub->start + 1;
	sub->l_techline.line[sub->l_techline.len] = 0;
	sub->start = 0;
	if (sub->end == g_techline.len)
			sub->l_techline.line[sub->l_techline.len] = END_T;
	sub->end = sub->l_techline.len;
	return (0);
}

int		erroring_andor_pipe(t_ltree *final, size_t *i, int tmp, size_t bl_end)
{
	if (*i == g_techline.len || g_techline.line[*i] == COMENT)
	{
		final->flags |= ERR_OUT;
		if ((tmp & LOG_AND) || (tmp & LOG_OR))
			g_prompt.prompt_func = cmdandor_prompt;
		else if (final->flags & PIPED_IN)
			g_prompt.prompt_func = pipe_prompt;
		return (OUT);
	}
	else if (*i == bl_end)
	{
		final->err_i = *i;
		final->flags |= ERR_OUT;
		final->flags |= ERR_REDIR << 16;
		ft_error_redir(final);
	}
	g_prompt.prompt_func = main_prompt;
	return (0);
}