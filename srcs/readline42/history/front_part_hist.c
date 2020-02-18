/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   front_part_hist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 13:14:32 by vladlenasku       #+#    #+#             */
/*   Updated: 2020/02/18 13:16:34 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

int					make_ctrl_r_history(void)
{
	unsigned short	len;
	unsigned short	len_x;
	char			*find;
	size_t			pos_back;
	int				coincidence;

	pos_back = g_rline.pos;
	position_relative(&len_x, 0, g_rline.cmd_len);
	position_cursor_for_menu(g_rline.cmd_len);
	len = 22;
	ft_putstr_fd("We search in history: ", STDOUT_FILENO);
	find = get_the_answer_hist(&len);
	clean_output_question(0, pos_back, len, len_x);
	if (find == NULL)
		return (OUT);
	coincidence = find_in_history(&find);
	if (coincidence < 0)
		return (incorrect_sequence());
	print_new_cmd_from_history(coincidence);
	return (OUT);
}

char			*get_the_answer_hist(unsigned short *len)
{
	char		*find;
	size_t		len_find;
	char		c;
	
	find = (char*)ft_xmalloc(CMD_SIZE + 1);
	c = 0;
	while (read(STDOUT_FILENO, &c, 1) && c != '\n') //add deletion
	{
		if (c == '\033')
			return (free_find_hist(&find));
		if ((c >= 0 && c < 2) || (c >= 4 && c < 32))
			continue;
		else if (c == '\003')
		{
			signal_ctrl_c();
			return (free_find_hist(&find));
		}
		else
			if (insert_valid_sy_hist(c,
				len, &find, &len_find) == 1)
				return (find);
	}
	if (find[0] == 0)
		return (free_find_hist(&find));
	return (find);
}

char			*free_find_hist(char **find)
{
	free(*find);
	return (NULL);
}

int				insert_valid_sy_hist(char c,
					unsigned short *len, char **find,
					size_t *len_find)
{
	if (ft_isprint(c) == 1)
	{
		if (*len >= g_screen.ws_col - 1)
			return (1);
		write(STDOUT_FILENO, &c, 1);
		*find = ft_straddsy(*find, c);
		*len_find = ft_strlen(*find);
		(*len)++;
		if (*len_find == CMD_SIZE - 1)
			return (1);
	}
	if (c == 127)
		backspace_one_sy(find, len_find, len);
	return (0);
}

int				backspace_one_sy(char **find, size_t *len_find,
					unsigned short *len)
{
	char		*tmp;
	
	tmp = *find;
	if (*len_find > 0)
	{
		tmp[*len_find - 1] = 0;
		(*len_find)--;
		(*len)--;
		write(STDOUT_FILENO, "\033[D \033[D", 7);
	}
	return (0);
}
