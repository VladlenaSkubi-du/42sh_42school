/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 12:23:25 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/20 13:03:04 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int				main(int argc, char **argv)
{
	char			*termtype;
	char			room_termtype[1024];

	if (!isatty(STDIN_FILENO))
		return (1);
	if (argc < 2 || (argv[1] = ft_strtrim(argv[1])) == NULL)
		return (usage());
	termtype = getenv("TERM");
	if (termtype == NULL || tgetent(room_termtype, termtype) != 1)
		return (terminal_errors(0));
	if (terminal_init_start(argc - 1, &argv[1]) < 0)
		return (terminal_errors(1));
	return (0);
}

char			*main_start_selection(int argc, const char **argv)
{
	t_args		*list;
	char		*result;
	size_t		max_len;
	int			flag;

	flag = 0;
	make_fullscreen();
	list = save_arguments(&max_len, argc, argv);
	save_for_exit(list, 1);
	resize_monitor(list, argc, max_len, &flag);
	result = read_commands(&list, &flag);
	reset_terminal_mode();
	if (list != NULL)
		free_arguments(list);
	return (result);
}

char			*generate_selected_line(t_args *list, char *result)
{
	char		**pointers;
	size_t		i;
	size_t		j;
	int			total;

	total = 0;
	j = -1;
	pointers = find_selected(list, &total, &j);
	if (total == 0)
	{
		free(pointers);
		return (NULL);
	}
	result = (char*)ft_xmalloc(total + 2 + (j - 1));
	i = -1;
	while (++i < j)
	{
		result = ft_strcat(result, pointers[i]);
		result = ft_straddsy(result, ' ');
	}
	result = ft_strcat(result, pointers[i]);
	free(pointers);
	return (result);
}

/*
** @*j and @total - all because of the norm, I'm sorry for that
*/

char			**find_selected(t_args *list, int *total, size_t *j)
{
	char		**pointers;
	t_args		*run;
	int			total_args_left;
	size_t		i;

	total_args_left = args_total(list, list);
	pointers = (char**)ft_xmalloc(sizeof(char*) * total_args_left + 1);
	pointers[total_args_left] = 0;
	run = list;
	i = -1;
	while (++i < (size_t)total_args_left)
	{
		if (run->selected == 1)
		{
			*total += run->len;
			pointers[++(*j)] = run->arg;
		}
		run = run->next;
	}
	return (pointers);
}
