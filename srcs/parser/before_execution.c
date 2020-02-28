/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 19:35:23 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/28 19:42:19 by rbednar          ###   ########.fr       */
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

int		before_exec(t_ltree *sub, t_ltree *block, t_list **list)
{
	int			err;
	
	sub->token = ft_find_token_sep(&g_cmd[sub->end]);
	ft_local_copy_lines(sub);
	pre_parsing_cut_glue(sub);
	if ((err = ft_find_redirection(sub)) & ERR_OUT)
	{
		ft_error_redir(sub);
		ft_lst_ltree_clear(list);
		return (OUT);
	}
	sub->envir = init_exec_environ();
	// if (assignment(sub) == CONTINUE)
		// sub->flags |= ERR_IN | ERR_CONT;
	// add_new_to_exec_env(&sub->envir, add);
	ft_substitution(sub);
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
	sub->ar_c = ft_count_words(&(sub->l_tline.line[0]), SPACE,
				sub->l_tline.len);
	sub->ar_v = (char **)ft_xmalloc(sizeof(char *) * (sub->ar_c + 1));
	i = 0;
	count = 0;
	while (count < sub->ar_c)
	{
		word = ft_give_me_word(&(sub->l_tline.line[p]), SPACE,
			sub->l_tline.len - p);
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
	sub->l_tline.line = ft_strndup(&g_techline.line[sub->start],
		sub->end - sub->start + 1);
	sub->l_tline.len = sub->end - sub->start;
	sub->l_tline.alloc_size = sub->end - sub->start + 1;
	sub->l_tline.line[sub->l_tline.len] = 0;
	sub->start = 0;
	if (sub->end == g_techline.len)
			sub->l_tline.line[sub->l_tline.len] = END_T;
	sub->end = sub->l_tline.len;
	return (0);
}

int		erroring_andor_pipe(t_ltree *final, size_t *i, int tmp, size_t bl_end)
{
	if (*i == g_techline.len || g_techline.line[*i] == COMENT)
	{
		final->flags |= ERR_OUT;
		if ((tmp & LOG_AND_OUT) || (tmp & LOG_OR_OUT))
			g_prompt.prompt_func = cmdandor_prompt;
		else if (final->flags & PIPED_IN)
			g_prompt.prompt_func = pipe_prompt;
		return (OUT);
	}
	else if (*i == bl_end || g_techline.line[*i] == PIPE ||
		g_techline.line[*i] == AND)
	{
		final->err_i = *i;
		final->err = ft_strndup(&g_cmd[*i], 2);
		final->flags |= ERR_OUT;
		final->flags |= ERR_REDIR << 16;
		if (final->err_i < g_techline.len)
			error_handler((SYNTAX_ERROR | (ERR_REDIR << 9)), final->err);
		else
			error_handler((SYNTAX_ERROR | (ERR_REDIR << 9)), "newline");
	}
	g_prompt.prompt_func = main_prompt;
	return (0);
}