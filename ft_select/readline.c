/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 12:24:09 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/20 12:58:06 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

char			*read_commands(t_args **list, int *flag)
{
	int			key;
	char		*result;

	result = NULL;
	while (1)
	{
		if (*flag != 1)
		{
			bell_sound();
			continue;
		}
		key = key_hook();
		if (key == '\033')
			return (NULL);
		if (key == '\n')
		{
			result = generate_selected_line(*list, result);
			return (result);
		}
		else
		{
			if (read_commands_and_signals(list, key, flag) == NULL)
				return (NULL);
		}
	}
}

char			*read_commands_and_signals(t_args **list, int key, int *flag)
{
	if (*flag != 1)
		return ("wait");
	if (key == 4283163 || key == 4348699 ||
			key == 4414235 || key == 4479771)
		make_movements(*list, key);
	(key == 32) ? select_element(*list) : 0;
	if (key == 126)
		if ((*list = delete_element(*list)) == NULL)
			return (NULL);
	if (key == 127)
	{
		if ((*list = backspace_element(*list)) == NULL)
			return (NULL);
	}
	return ("ok");
}

int				key_hook(void)
{
	char		buffer[4];

	ft_bzero(buffer, 4);
	read(STDIN_FILENO, buffer, 3);
	return (*(unsigned int*)buffer);
}
