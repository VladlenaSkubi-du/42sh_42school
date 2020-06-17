#include "shell42.h"
#include "readline.h"

/*
** @pos_x is absolute calculation of position you have NOW,
** because changes will be visible in global structure @g_rline
** g_rline.pos should be changed after the call of these functions
*/

int					front_move_one_char_right(int pos_x)
{
	if (pos_x >= 0 && pos_x < g_screen.ws_col - 1 &&
			g_rline.cmd[g_rline.pos] != '\n')
	{
		tputs(g_cap.nd, 1, printc);
		g_rline.pos_x++;
	}
	else if (pos_x == g_screen.ws_col - 1 ||
		g_rline.cmd[g_rline.pos] == '\n')
	{
		tputs(g_cap.cr, 1, printc);
		tputs(g_cap.dow, 1, printc);
		g_rline.pos_x = 0;
		g_rline.pos_y++;
	}
	else
		return (1);
	return (0);
}

/*
** @pos_x is absolute calculation of position you have NOW,
** because changes will be visible in global structure @g_rline
** g_rline.pos should be changed after the call of these functions
*/

int					front_move_one_char_left(int pos_x)
{
	int				prev_x;

	prev_x = 0;
	if (pos_x > 0)
	{
		tputs(g_cap.le, 1, printc);
		g_rline.pos_x--;
	}
	else if (pos_x == 0)
	{
		if (g_rline.pos > 0 &&
			g_rline.cmd[g_rline.pos - 1] == '\n')
			prev_x = count_x_position_new_line(g_rline.pos - 2);
		else
			prev_x = g_screen.ws_col - 1;
		position_cursor("ch", 0, prev_x);
		tputs(g_cap.up, 1, printc);
		g_rline.pos_x = prev_x;
		g_rline.pos_y--;
	}
	else
		return (1);
	return (0);
}

/*
** All the "interactive" questions to user from shell are orange
** and inserted through this function. in order to use readline
** "engine" - the length of comments, position for each letter in
** terminal (x and y) are also counted
*/

int					front_insert_by_letters(char *str, int *pos_x)
{
	int				i;

	i = 0;
	while (str[i])
	{
		front_insert_one_char(str[i], *pos_x, 'c', ORANGE);
		(*pos_x)++;
		if (*pos_x == g_screen.ws_col)
			*pos_x = 0;
		i++;
	}
	return (0);
}

/*
** The functions helps to count to what position on the upper
** line the coursor should jump. There can be three situations:
** 1.1) width of terminal:
** upper line      |prompt > aaa|
** line we are on  |X           |
** @nl_pos will be (g_rline.pos - 2) == 1
** we go "left" in backend untill position is zero and though we
** do not have any "\n", we do prompt len + 1 + 1 and jump to
** the width of terminal
** 1.2) width of terminal:
** upper-upper line|prompt > aaa|
** upper line      |aaaaaaaaaaaa|
** line we are on  |X           |
** @nl_pos will be (g_rline.pos - 2) == 13
** we go "left" in backend untill position is zero and though we
** do not have any "\n", we do prompt len + 13 + 1 and though it
** is more than terminal width, find modular after division by
** terminal width
** 2.1) "\n" in the line ('N' for dispatch)
** upper line      |prompt > aN |
** line we are on  |X           |
** @nl_pos will be (g_rline.pos - 2) == 0
** we get that len is 0 and the zero-element is not '\n'
** so the x-position to jump on is prompt len + 0 + 1
** 2.2) "\n" in the line ('N' for dispatch)
** upper line      |prompt > N  |
** line we are on  |X           |
** @nl_pos will be (g_rline.pos - 2) == -1
** so the x-position to jump on is prompt len
** 2.3) "\n" in the line ('N' for dispatch)
** upper-upper line|prompt > N  |
** upper line      |aN          |
** line we are on  |X           |
** @nl_pos will be (g_rline.pos - 2) == 1
** we get that len is 1 and the zero-element is '\n'
** so we do not add the prompt-len, because we know that we
** are not on the 0-line - return the x-position 1
** 3.1) width of terminal + "\n" in the line ('N' for dispatch)
** upper-upper line|prompt > aaa|
** upper line      |aaaN        |
** line we are on  |X           |
** @nl_pos will be (g_rline.pos - 2) == 5
** we go "left" in backend untill position is zero and though we
** do not have any "\n", we do prompt len + 5 + 1 and though it
** is more than terminal width, find modular after division by
** terminal width
** 3.2) width of terminal + "\n" in the line ('N' for dispatch)
** upper-upper line|prompt > aN |
** upper-upper line|aaaaaaaaaaaa|
** upper line      |aaaN        |
** line we are on  |X           |
** @nl_pos will be (g_rline.pos - 2) == 16
** we go "left" in backend untill position is zero and though we
** do have another "\n" on the way, we stop and so we have len = 15,
** it is more than terminal width, so we find modular after
** division by terminal width
*/

int					count_x_position_new_line(int nl_pos)
{
	int				len;
	
	len = 0;
	if (nl_pos < 0)
		return (g_prompt.prompt_len);
	while (nl_pos)
	{
		len++;
		if (g_rline.cmd[nl_pos] == '\n')
			break ;
		nl_pos--;
	}
	if (nl_pos > 0)
		len -= 1;
	else if (nl_pos == 0 && g_rline.cmd[nl_pos] != '\n')
		len += g_prompt.prompt_len + 1;
	if (len >= g_screen.ws_col)
		len = len % g_screen.ws_col;
	return (len);
}

/*
** @direction can be left = 'l' or right = 'r'
** controls stopping (not to move
** too far left or right) and backend counting
** of position
*/

int					move_cursor_from_old_position(int pos_old,
						char direction)
{
	if (direction == 'l')
	{
		while (g_rline.pos != pos_old)
		{
			if (front_move_one_char_left(g_rline.pos_x))
				return (incorrect_sequence());
			g_rline.pos--;
		}
	}
	if (direction == 'r')
	{
		while (g_rline.pos != pos_old)
		{
			if (front_move_one_char_right(g_rline.pos_x))
				return (incorrect_sequence());
			g_rline.pos++;
		}
	}
	return (0);
}