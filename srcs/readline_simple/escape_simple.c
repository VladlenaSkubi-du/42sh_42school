/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_simple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 16:03:22 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/23 14:52:19 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int				sescape_check(char **seq_base)
{
	size_t	i;
	char	buff[16];
	int		stage;

	i = 0;
	ft_bzero(buff, 16);
	while (read(STDIN_FILENO, buff + i, 1))
	{
		stage = 0;
		while (stage < SESC_NUM)
		{
			if (!ft_strncmp(buff, seq_base[stage], i + 1))
				break ;
			stage++;
		}
		if (stage == SESC_NUM)
			return (bell_sound());
		if (!ft_strncmp(buff, seq_base[stage], ft_strlen(seq_base[stage]) + 1))
			return (ssequence_process(stage));
		i++;
	}
	return (0);
}

int				ssequence_process(int sequence_num) //добавить историю
{
	int				(*seq_action[SESC_NUM])(void);

	seq_action[0] = sesc_right;
	seq_action[1] = key_up_proc;
	seq_action[2] = sesc_left;
	seq_action[3] = key_down_proc;
	seq_action[4] = sesc_r;
	return ((*seq_action[sequence_num])());
}

int				sesc_left(void)
{
	if (g_rline.pos == 0)
		return (bell_sound());
	g_rline.pos--;
	write(STDOUT_FILENO, "\033[D", 3);
	return (0);
}

int				sesc_right(void)
{
	if (g_rline.pos >= ft_strlen(g_rline.cmd) ||
		g_rline.pos + g_rline.prompt_len == g_screen.ws_col)
		return (bell_sound());
	g_rline.pos++;
	write(STDOUT_FILENO, "\033[C", 3);
	return (0);
}

int				sesc_r(void)
{
	while (g_rline.pos < ft_strlen(g_rline.cmd) &&
		g_rline.pos + g_rline.prompt_len < g_screen.ws_col - 1)
		sesc_right();
	while (g_rline.pos)
		sbackspace_proc();
	return (0);
}