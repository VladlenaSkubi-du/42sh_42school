/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esc_t.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 14:56:57 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/24 13:31:50 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "readline.h"

/*
** @flag = 'o' means we are within the word and jump to the left
** will be to the beginning of the word we are on
**       = 'n' means we are on the sign or in the beginning of
** the word so the jump will be to the word before
** If you are on the first word in a command or something goes
** wrong - you get incorrect_sequence(): bell and out;
*/

int			esc_t(void)
{
	size_t			pos_back;
	char			flag;
	char			*end;
	char			*word_first;
	size_t			fi;

	if (g_rline.pos == 0)
		return (incorrect_sequence());
	undo(0);
	pos_back = g_rline.pos;
	flag = (ft_isalnum(g_rline.cmd[g_rline.pos]) &&
		ft_isalnum(g_rline.cmd[g_rline.pos - 1])) ? 'o' : 'n';
	if (esc_t_first_left(flag, pos_back))
		return (1);
	word_first = save_word(&fi, g_rline.cmd, g_rline.pos);
	if (pos_back == g_rline.cmd_len)
		return (esc_t_len_pos(word_first, fi, pos_back));
	end = save_end(pos_back);
	if (flag == 'o')
		esc_t_need_left(word_first, fi, end);
	else
		esc_t_need_right(word_first, fi, end);
	free(word_first);
	free(end);
	return (0);
}

int			esc_t_first_left(char flag, size_t pos_back)
{
	if (word_left_proc())
		return (1);
	if (g_rline.pos == 0 && flag == 'o')
	{
		swap_ints((int*)&g_rline.pos, (int*)&pos_back);
		move_cursor_from_old_position(pos_back, 'r');
		return (incorrect_sequence());
	}
	return (0);
}

int			esc_t_need_left(char *word_first, size_t fi, char *end)
{
	char			*word_second;
	size_t			se;
	size_t			pos_old;
	char			delimiter;

	pos_old = g_rline.pos;
	delimiter = g_rline.cmd[g_rline.pos - 1];
	if (word_left_proc())
		return (0);
	word_second = save_word(&se, g_rline.cmd, g_rline.pos);
	ft_strcpy(g_rline.cmd + g_rline.pos, word_first);
	g_rline.cmd[g_rline.pos + fi] = delimiter;
	ft_strcpy(g_rline.cmd + g_rline.pos + fi + 1, word_second);
	ft_strcpy(g_rline.cmd + g_rline.pos + fi + 1 + se, end);
	putcap("cd");
	ft_putstr_fd(g_rline.cmd + g_rline.pos, 1);
	g_rline.pos = pos_old + fi;
	move_cursor_back_after_print(0);
	free(word_second);
	return (0);
}

int			esc_t_need_right(char *word_first, size_t fi, char *end)
{
	char			*word_second;
	size_t			se;
	size_t			pos_old;
	char			delimiter;

	pos_old = g_rline.pos;
	if (word_right_proc())
		return (0);
	delimiter = g_rline.cmd[g_rline.pos];
	word_second = save_word(&se, g_rline.cmd, g_rline.pos + 1);
	ft_strcpy(g_rline.cmd + pos_old, word_second);
	g_rline.cmd[pos_old + se] = delimiter;
	ft_strcpy(g_rline.cmd + pos_old + se + 1, word_first);
	ft_strcpy(g_rline.cmd + pos_old + se + 1 + fi, end);
	swap_ints((int*)&g_rline.pos, (int*)&pos_old);
	move_cursor_from_old_position(pos_old, 'l');
	putcap("cd");
	ft_putstr_fd(g_rline.cmd + g_rline.pos, 1);
	g_rline.pos = pos_old + 1 + se;
	move_cursor_back_after_print(0);
	free(word_second);
	return (0);
}

int			esc_t_len_pos(char *word_first, size_t fi, size_t pos_back)
{
	char			*word_second;
	size_t			se;
	char			delimiter;

	delimiter = g_rline.cmd[g_rline.pos - 1];
	if (word_left_proc())
		return (0);
	word_second = save_word(&se, g_rline.cmd, g_rline.pos);
	ft_strcpy(g_rline.cmd + g_rline.pos, word_first);
	g_rline.cmd[g_rline.pos + fi] = delimiter;
	ft_strcpy(g_rline.cmd + g_rline.pos + fi + 1, word_second);
	putcap("cd");
	ft_putstr_fd(g_rline.cmd + g_rline.pos, 1);
	if (g_rline.cmd_len + g_rline.prompt_len ==
		g_screen.ws_col * g_rline.str_num)
		putcap("sf");
	g_rline.pos = pos_back;
	free(word_first);
	free(word_second);
	return (0);
}
