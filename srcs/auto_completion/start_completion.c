/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_completion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 15:27:02 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/04 18:59:41 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static char			sign_means(char c, char flag)
{
	if (flag == 'b')
	{
		if (c == '#' || c == '%' || c == '!' || c == '@' || c == '"'
			|| c == '\\' || c == '^' || c == '*' || c == '(' || c == ')'
			|| c == '[' || c == ']' || c == '{' || c == '}' || c == ':'
			|| c == '=' || c == '/' || c == ',' || c == '\'' || c == '-')
			return (1);
	}
	else
	{
		if (c == ';' || c == '&' || c == '|' || c == ' ')
			return (1);
	}
	return (0);
}

static char			*return_pool(int *pool, size_t i, size_t j, size_t k)
{
	if ((k == 0 || g_rline.cmd[k] == ';' || g_rline.cmd[k] == '&'
		|| g_rline.cmd[k] == '|') && j == i)
	{
		*pool = 4;
		return (NULL);
	}
	if ((k == 0 || g_rline.cmd[k] == ';' || g_rline.cmd[k] == '&'
		|| g_rline.cmd[k] == '|') && j > i && sign_means(g_rline.cmd[i], 'c'))
		*pool = 1;
	else if (g_rline.cmd[i] == '$')
		*pool = 2;
	else if (ft_isalnum(g_rline.cmd[i]) || g_rline.cmd[i] == '.')
		*pool = 3;
	else
	{
		// printf("k = %zu, i = %zu, j = %zu\n", k, i, j);
		*pool = 0;
	}
	return (ft_strndup(g_rline.cmd + i, j - i));
}

static char			*choose_pool(size_t pos_back, int *pool) //восклицательный знак становится \!, как и '\',
//звездочка и бэкслеш сразу переключает на аргументы
//не ищутся при: #, %, @ (у нас),^, =, :, -, ',', ?
//ищутся со знаками, точка
//ищутся, не влияют знаки (они убираются): {}, [], (), "", ''
{
	size_t			beg_word;
	size_t			end_word;
	size_t			space;

	beg_word = g_rline.pos;
	end_word = beg_word;
	if (!ft_isalnum(g_rline.cmd[beg_word]) && beg_word - 1 > 0
		&& ft_isalnum(g_rline.cmd[beg_word - 1]))
		beg_word--;
	while (beg_word > 0 && ft_isalnum(g_rline.cmd[beg_word]))
		beg_word--;
	if (beg_word > 0)
		beg_word++;
	while (g_rline.cmd[end_word] && end_word < g_rline.pos
		&& ft_isalnum(g_rline.cmd[end_word]))
		end_word++;
	space = beg_word;
	while (space > 0 && g_rline.cmd[space] == ' ')
		space--;
	return (return_pool(pool, beg_word, end_word, space));
}

/*
** @pool = pool of variables: binary-files (1), variables (2),
** arguments (3), comment (4), bell (nothing can be done - 0);
** @complete - is a string, according to which we search
** options for completion
** @tab_push is a counter according to that we complete this or that line
** from the menu
*/

int					auto_completion(void)
{
	size_t			len;
	size_t			pos_back;
	int				pool;
	char			*complete;
	
	len = ft_strlen(g_rline.cmd);
	pos_back = g_rline.pos;
	complete = choose_pool(pos_back, &pool);
	printf("pool - %d, %s\n", pool, complete);
	if (pool == 0)
		return (incorrect_sequence());
	// print_menu(len, pos_back, pool, complete);
	return (0);
}

/*
** Here we get array depending on the @pool: binary, alphabet, arguments or
** variables
** A routing function
*/

static char			**get_menu(char pool, t_completion *menu_buf)
{
	char			**menu;

	menu = (char**)ft_xmalloc((sizeof(char*) * (10 + 1))); // if (pool == 'c')
	menu[10] = 0;
	menu[0] = "la";
	menu[1] = "ls";
	menu[2] = "lp";
	menu[3] = "lo";
	menu[4] = "llll";
	menu[5] = "lk";
	menu[6] = "ly";
	menu[7] = "lg";
	menu[8] = "lw";
	menu[9] = "lh";
	menu_buf->word_len = 8;
	menu_buf->word_nb = 10;
	// {
	// 	menu = "Please, choose a letter.\nThere are too many binaries:\n"; //придумать, как возвращать алфавит
	// }
	return (menu);
}

/*
** The front-part: we put cursor to the end of the line -
** only within the line we can use functions from cursor_position.c file
** because they use g_rline.pos - after that we print the menu-buffer
** and put the cursor back to the end of the cmd-line
** and back to the old position
**
** @menu_lines_num we need to understand how high we need to jump
** to the end of the cmd-line after the menu-printing
**
** The back-part: menu-buffer is filled in in the output_buffer.c file
*/

int					print_menu(size_t len, size_t pos_back,
						char pool, char *complete)
{
	char			**menu;
	t_completion	menu_buf;
	unsigned short	len_x;
	static int		tab_push;
	size_t			i;

	tab_push = (g_rline.flag & TAB) ? tab_push + 1 : -1;
	g_rline.flag |= TAB;
	i = -1;
	position_relative(&len_x, 0, len);
	position_cursor_for_menu(len);
	menu_buf_init(&menu_buf);
	menu = get_menu(pool, &menu_buf);
	while (++i < menu_buf.word_nb)
		buffer_col_print(menu[i], &menu_buf);
	position_cursor_after_menu_back(len_x, menu_buf.buf_lines, pos_back, len);
	return (0);
}

int					check_menu(void) //поправить возврат после нажатия символа
{
	if (g_rline.flag & TAB)
	{
		clean_menu();
		g_rline.flag &= ~TAB;
	}
	return (0);
}

int					clean_menu(void)
{
	size_t			len;
	size_t			pos_back;

	len = ft_strlen(g_rline.cmd);
	pos_back = g_rline.pos;
	position_cursor_for_menu(len);
	putcap("cd");
	g_rline.pos = pos_back;
	move_cursor_from_old_position(len, 'l');
	return (0);
}