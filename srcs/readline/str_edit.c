#include "shell42.h"
#include "readline.h"

int					str_shift(char *str, int shift) //TODO check
{
	char			*buff;

	buff = (char *)ft_xmalloc(ft_strlen(str) + 1);
	ft_strcpy(buff, str);
	ft_strcpy(str + shift, buff);
	free(buff);
	return (0);
}

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
	insert_char(c, color);
	return (0);
}

int					char_add_without_undo(char c, char *color)
{
	if (g_rline.cmd_len >= g_rline.cmd_buff_len - 1)
	{
		g_rline.cmd = (char *)ft_realloc(g_rline.cmd, g_rline.cmd_len,
			g_rline.cmd_buff_len,
			g_rline.cmd_buff_len + CMD_SIZE);
		g_rline.cmd_buff_len += CMD_SIZE;
	}
	g_rline.cmd_len++;
	insert_char(c, color);
	return (0);
}

/*
** putcap("cd") - clearing till the end of the screen
** putcap("sf") - if cmd-line finishes of the most right position in terminal,
** the cursor should jump to the next line
*/

int					insert_char(char c, char *color)
{
	if (g_rline.cmd[g_rline.pos] != '\0')
	{
		str_shift(g_rline.cmd + g_rline.pos, 1);
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
