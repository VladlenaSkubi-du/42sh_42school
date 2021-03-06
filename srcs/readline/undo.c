/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 20:36:49 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/25 20:39:10 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"
#define ACTIONS_MAX 10

t_action_stack	*action_new(void)
{
	t_action_stack			*new;

	new = (t_action_stack *)ft_xmalloc(sizeof(t_action_stack));
	new->cmd_b = (char*)ft_xmalloc(g_rline.cmd_buff_len + 1);
	ft_strcpy(new->cmd_b, g_rline.cmd);
	new->pos_b = g_rline.pos;
	new->num_b = g_rline.str_num;
	new->next = 0;
	new->prev = 0;
	return (new);
}

int				action_add(t_action_stack **start,
					t_action_stack **end, int *num)
{
	t_action_stack			*new;

	new = action_new();
	if (!(*start))
	{
		*start = new;
		*end = *start;
		return (0);
	}
	(*start)->prev = new;
	new->next = *start;
	*start = new;
	(*num)++;
	return (0);
}

void			action_alloc_management(t_action_stack **start, int mode)
{
	static t_action_stack	**save;
	t_action_stack			*temp;

	if (!mode)
		save = start;
	else if (save)
	{
		while (*save)
		{
			temp = (*save)->next;
			free((*save)->cmd_b);
			free(*save);
			*save = temp;
		}
		*save = NULL;
	}
}

void			action_pull(t_action_stack **start, int *num)
{
	t_action_stack			*temp;
	int						i;

	if (start && *start)
	{
		temp = *start;
		clear_whole_line();
		i = -1;
		while ((*start)->cmd_b[++i])
			char_add_without_undo((*start)->cmd_b[i], NULL);
		while (g_rline.pos != (*start)->pos_b)
			arrow_left_jumpcharleft();
		*start = (*start)->next;
		*start && ((*start)->prev = 0);
		free(temp->cmd_b);
		free(temp);
		(*num)--;
	}
}

int				undo(int mode)
{
	static t_action_stack	*actions = 0;
	static t_action_stack	*end = 0;
	static int				actions_num = 0;

	if (!mode)
		action_add(&actions, &end, &actions_num);
	else if (actions_num)
		action_pull(&actions, &actions_num);
	else
		incorrect_sequence();
	action_alloc_management(&actions, 0);
	if (actions_num >= ACTIONS_MAX)
	{
		end = end->prev;
		free(end->next->cmd_b);
		free(end->next);
		end->next = 0;
		actions_num--;
	}
	return (0);
}
