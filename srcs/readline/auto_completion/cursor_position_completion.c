#include "shell42.h"
#include "readline.h"

int					position_cursor_for_menu(int len)
{
	if (g_rline.pos == 0 && len == 0)
		tputs(g_cap.sf, 1, printc);
	else
	{
		move_cursor_from_old_position(len, 'r');
		tputs(g_cap.sf, 1, printc);
	}
	return (0);
}

int					position_cursor_after_menu_back(int len_x, int len_y,
						int buf_lines, int pos_back)
{
	int				i;
	int				jump;

	i = -1;
	position_cursor("ch", 0, len_x);
	while (++i < buf_lines)
		putcap("sr");
	if (g_rline.pos_x == 0 && g_rline.pos_y == g_rline.str_num &&
		pos_back != g_rline.cmd_len)
		tputs(g_cap.up, 1, printc);
	if (g_rline.str_num > 1)
	{
		jump = g_rline.str_num - 1 - len_y;
		if (jump > 1)
			position_cursor("UP", 0, jump);
		else if (jump == 1)
			tputs(g_cap.up, 1, printc);
	}
	g_rline.pos = pos_back;
	g_rline.pos_x = len_x;
	g_rline.pos_y = len_y;
	return (0);
}
