/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_initiation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:31:44 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/20 13:03:38 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_args			*save_arguments(size_t *max_len, int argc, const char **argv)
{
	t_args		*list;
	t_args		*run;
	size_t		i;

	list = init_first_argument(argv[0]);
	*max_len = list->len;
	run = list;
	i = 0;
	while (++i < (size_t)argc)
	{
		if ((argv[i] = ft_strtrim(argv[i])) == NULL)
			continue ;
		init_next_argument(run, argv[i], i);
		if (run->len > *max_len)
			*max_len = run->len;
		run = run->next;
	}
	*max_len = (*max_len == 8) ? (*max_len)++ : *max_len;
	while (*max_len % 8 != 0)
		(*max_len)++;
	return (list);
}

t_args			*init_first_argument(const char *argument)
{
	t_args		*list;

	list = ft_xmalloc(sizeof(t_args));
	list->arg = ft_strdup(argument);
	list->len = ft_strlen(argument);
	list->next = list;
	list->prev = list;
	list->selected = 0;
	list->underline = 1;
	list->x = 0;
	list->y = 0;
	return (list);
}

void			init_next_argument(t_args *current,
					const char *argument, short flag)
{
	t_args		*tmp;
	t_args		*save;

	tmp = ft_xmalloc(sizeof(t_args));
	tmp->arg = ft_strdup(argument);
	tmp->len = ft_strlen(argument);
	tmp->selected = 0;
	tmp->underline = 0;
	tmp->x = 0;
	tmp->y = 0;
	if (flag == 1)
	{
		tmp->next = current;
		current->next = tmp;
		tmp->prev = current;
		current->prev = tmp;
	}
	else
	{
		save = current->next;
		tmp->next = save;
		current->next = tmp;
		tmp->prev = current;
		save->prev = tmp;
	}
}
