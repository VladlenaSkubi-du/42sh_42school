#include "shell42.h"
#include "readline.h"

int					count_x_position_new_line(size_t nl_pos)
{
	int				len;
	
	len = 0;
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
		len += g_rline.prompt_len + 1;
	if (len >= g_screen.ws_col)
		len = len % g_screen.ws_col;
	return (len);
}

/*
** @direction can be left = 'l' or right = 'r'
*/

int					move_cursor_from_old_position(size_t pos_old,
						char direction)
{
	if (direction == 'l')
	{
		while (g_rline.pos != pos_old)
		{
			front_move_one_char_left(g_rline.pos_x);
			g_rline.pos--;
		}
	}
	if (direction == 'r')
	{
		while (g_rline.pos != pos_old)
		{
			front_move_one_char_right(g_rline.pos_x);
			g_rline.pos++;
		}
	}
	return (0);
}

/*
** @Flag == 1 means "save position"
** @flag == 0 means "return position"
*/

int					front_set_cursor_jmp(size_t *pos, int *pos_x,
						int *pos_y, int flag)
{
	static size_t	pos_save;
	static int		pos_x_save;
	static int		pos_y_save;
	
	if (flag == 1)
	{
		pos_save = *pos;
		pos_x_save = *pos_x;
		pos_y_save = *pos_y;
	}
	if (flag == 0)
	{
		*pos = pos_save;
		*pos_x = pos_x_save;
		*pos_y = pos_y_save;
	}
	return (0);
}