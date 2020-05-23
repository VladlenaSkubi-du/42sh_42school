#include "shell42.h"
#include "readline.h"

/*
** @pos_x is absolute calculation of position you have NOW,
** because changes will be visible in global structure @g_rline
** g_rline.pos should be changed after the call of these functions
*/

int					front_move_one_char_right(int pos_x)
{
	if (pos_x > 0 && pos_x < g_screen.ws_col - 1 &&
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
*/

int					front_insert_by_letters(char *str, int *pos_x)
{
	int				i;

	i = 0;
	while (str[i])
	{
		front_insert_one_char(str[i], *pos_x, 'c', ORANGE);
		(*pos_x) = i;
		if (*pos_x == g_screen.ws_col - 1)
			*pos_x = 0;
		i++;
	}
	return (0);
}

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
	else
		len += g_prompt.prompt_len + 1;
	if (len >= g_screen.ws_col)
		len = len % g_screen.ws_col;
	return (len);
}

/*
** @direction can be left = 'l' or right = 'r'
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