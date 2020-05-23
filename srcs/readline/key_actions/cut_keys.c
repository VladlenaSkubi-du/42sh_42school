#include "shell42.h"
#include "readline.h"

int					backspace_process(void)
{
	char			*swap;
	int				len_swap;

	check_menu();
	if (g_rline.pos > 0)
	{
		undo(0);
		swap = g_rline.cmd + g_rline.pos;
		len_swap = ft_strlen(swap);
		if (g_rline.cmd[g_rline.pos - 1] == '\n')
			return (backspace_newline(swap, len_swap));
		ft_strcpy(g_rline.cmd + g_rline.pos - 1, swap);
		ft_bzero(g_rline.cmd + g_rline.pos - 1 + len_swap,
			g_rline.cmd_buff_len - g_rline.cmd_len);
		g_rline.cmd_len--;
		key_left_proc();
		front_set_cursor_jmp(&g_rline.pos, &g_rline.pos_x,
			&g_rline.pos_y, 1);
		tputs(g_cap.cd, 1, printc);
		front_insert_cmd_till_the_end(g_rline.pos_y + 1);
	}
	else
		return (incorrect_sequence());
	return (0);
}

int					backspace_newline(char *swap, int len_swap)
{
	int				pos_back;

	pos_back = g_rline.pos;
	key_left_proc();
	front_set_cursor_jmp(&g_rline.pos, &g_rline.pos_x,
		&g_rline.pos_y, 1);
	ft_strcpy(g_rline.cmd + pos_back - 1, swap);
	ft_bzero(g_rline.cmd + pos_back - 1 + len_swap,
		g_rline.cmd_buff_len - g_rline.cmd_len);
	g_rline.cmd_len--;
	tputs(g_cap.cd, 1, printc);
	front_insert_cmd_till_the_end(g_rline.pos_y + 1);
	return (0);
}

int					delete_process(void)
{
	char			*swap;
	int				len_swap;

	check_menu();
	if (g_rline.pos == 0 && g_rline.cmd_len == 0)
	{
		if (route_exit() == OUT)
			return (OUT);
	}
	if (g_rline.pos < g_rline.cmd_len)
	{
		undo(0);
		swap = g_rline.cmd + g_rline.pos + 1;
		len_swap = ft_strlen(swap);
		ft_strcpy(g_rline.cmd + g_rline.pos, swap);
		ft_bzero(g_rline.cmd + g_rline.pos + len_swap,
			g_rline.cmd_buff_len - g_rline.cmd_len);
		g_rline.cmd_len--;
		front_set_cursor_jmp(&g_rline.pos, &g_rline.pos_x,
			&g_rline.pos_y, 1);
		tputs(g_cap.cd, 1, printc);
		front_insert_cmd_till_the_end(g_rline.pos_y + 1);
	}
	else
		return (incorrect_sequence());
	return (0);
}

int					delete_till_compl(int delete)
{
	char			*swap;
	int				len_swap;
	int				i;

	if (g_rline.pos > 0)
	{
		swap = g_rline.cmd + g_rline.pos;
		len_swap = ft_strlen(swap);
		ft_strcpy(g_rline.cmd + g_rline.pos - delete, swap);
		ft_bzero(g_rline.cmd + g_rline.pos - delete + len_swap,
			g_rline.cmd_buff_len - ft_strlen(g_rline.cmd));
		g_rline.cmd_len -= delete;
		i = -1;
		while (++i < delete)
			key_left_proc();
		front_set_cursor_jmp(&g_rline.pos, &g_rline.pos_x,
			&g_rline.pos_y, 1);
		tputs(g_cap.cd, 1, printc);
		front_insert_cmd_till_the_end(g_rline.pos_y + 1);
	}
	else
		return (incorrect_sequence());
	return (0);
}
