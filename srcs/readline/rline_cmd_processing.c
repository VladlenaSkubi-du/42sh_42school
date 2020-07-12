#include "shell42.h"
#include "readline.h"

/*
** Controls the length of the backend buffer and "stoppings"
** not to have errors, is used for user input
*/

int					char_add(char c, char *color)
{
	if (g_rline.cmd_len >= g_rline.cmd_buff_len - 1)
	{
		g_rline.cmd = (char *)ft_realloc(g_rline.cmd, g_rline.cmd_len,
			g_rline.cmd_buff_len,
			g_rline.cmd_buff_len + CMD_SIZE);
		g_rline.cmd_buff_len += CMD_SIZE;
	}
	undo(0);
	g_rline.cmd_len++;
	if (g_rline.cmd_len + 1 < 0 || g_rline.cmd_buff_len + 1 < 0)
		return (OUT);
	insert_char(c, color);
	return (0);
}

/*
** Controls the length of the backend buffer and "stoppings"
** not to have errors, is used for program input after some
** actions for the frontend and backend insert, for instance:
** to insert line from history, auto-completion word or the line
** saved in paste-buffer or undo-buffer
*/

int					char_add_without_undo(char c, char *color)
{
	if (g_rline.cmd_len >= g_rline.cmd_buff_len - 1)
		realloc_readline_cmd();
	g_rline.cmd_len++;
	if (g_rline.cmd_len + 1 < 0 || g_rline.cmd_buff_len + 1 < 0)
		return (OUT);
	insert_char(c, color);
	return (0);
}

/*
** We can insert to the end of the cmd-line and in the middl of it
** putcap("cd") - clearing till the end of the screen
** putcap("sf") - if cmd-line finishes on the most right position in terminal,
** the cursor should jump to the next line
** By insertion g_rline structure remembers real pos_x and pos_y positions,
** for example, after "sf" or "\n" insertion pos_x and pos_y will change
** (pos will not change because there were no user movements of the cursor)
*/

int					insert_char(char c, char *color)
{
	if (g_rline.cmd[g_rline.pos] != '\0')
	{
		ft_strshift(g_rline.cmd + g_rline.pos, 1);
		g_rline.cmd[g_rline.pos] = c;
		tputs(g_cap.cd, 1, printc);
		front_insert_one_char(g_rline.cmd[g_rline.pos], g_rline.pos_x, 'm', color);
		g_rline.pos++;
		front_set_cursor_jmp(&g_rline.pos, &g_rline.pos_x,
			&g_rline.pos_y, 1);
		front_insert_cmd_till_the_end(g_rline.pos_y + 1);
	}
	else
	{
		g_rline.cmd[g_rline.pos] = c;
		g_rline.pos++;
		front_insert_one_char(c, g_rline.pos_y, 'm', color);
	}
	return (0);
}

/*
** Is used to insert the part of line after cursor after actions done,
** for example: paste, cut of a word or a char and so on
** Inserts starting from cursor and moves cursor to the position
** needed after the action
*/

int					front_insert_cmd_till_the_end(int str_num_print)
{
	int				pos_back;
	int				pos_x_back;
	int				pos_y_back;

	if (g_rline.pos > 0 && g_rline.pos_x == 0 &&
			g_rline.cmd[g_rline.pos - 1] != '\n')
		g_rline.str_num = str_num_print - 1;
	else
		g_rline.str_num = str_num_print;
	while (g_rline.pos < g_rline.cmd_len)
	{
		front_insert_one_char(g_rline.cmd[g_rline.pos], g_rline.pos_x, 'm', NULL);
		g_rline.pos++;
	}
	front_set_cursor_jmp(&pos_back, &pos_x_back, &pos_y_back, 0);
	move_cursor_from_old_position(pos_back, 'l');
	return (0);
}

/*
** @Flag == 1 means "save position"
** @flag == 0 means "return position"
*/

int					front_set_cursor_jmp(int *pos, int *pos_x,
						int *pos_y, int flag)
{
	static int		pos_save;
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