#include "readline.h"

int				str_shift(char *str, int shift)
{
	char	*buff;

	buff = (char *)ft_xmalloc(ft_strlen(str));
	ft_strcpy(buff, str);
	ft_strcpy(str + shift, buff);
	free(buff);
	return (0);
}

void			backspace_process(void)
{
<<<<<<< HEAD
	// if (g_rline.pos != 0)
	// {
	// 	ft_strcpy(g_rline.cmd + g_rline.pos - 1, g_rline.cmd + g_rline.pos);
	// 	write(1, "\b", 1);
	// 	g_rline.pos--;
	// 	putcap("sc");
	// 	ft_putstr( g_rline.cmd + g_rline.pos);
	// 	write(1, " \b", 2);
	// 	putcap("rc");
	// }
=======
	if (g_rline.pos != 0)
	{
		ft_strcpy(g_rline.cmd + g_rline.pos - 1, g_rline.cmd + g_rline.pos);
		write(1, "\b", 1);
		g_rline.pos--;
		putcap("sc");
		ft_putstr( g_rline.cmd + g_rline.pos);
		write(1, " \b", 2);
		putcap("rc");
	}
>>>>>>> refs/remotes/origin/readline
}

int				char_add(char c)
{
	static size_t	sz_max = CMD_SIZE + 1;
	static size_t	sz = 0;

	if (sz >= sz_max)
	{
		if (!(g_rline.cmd = (char *)ft_realloc(g_rline.cmd, sz_max, sz_max,
			sz_max + CMD_SIZE)))
			return (-1);
		sz_max += CMD_SIZE;
	}
	if (g_rline.cmd[g_rline.pos] != '\0')
	{
		if (str_shift(g_rline.cmd + g_rline.pos, 1))
			return (-1);
		g_rline.cmd[g_rline.pos] = c;
		g_rline.str_num = count_str_num(); //put it also if we catch the signal SIGWINCH
		if (insert_within_string_termcap(c))
			return (-1);
	}
	else
	{
		g_rline.cmd[g_rline.pos] = c;
		g_rline.str_num = count_str_num(); //put it also if we catch the signal SIGWINCH
		if (g_rline.pos + g_rline.prompt_len + 1 == g_screen.ws_col * g_rline.str_num)
			putcap("sf");
	}
	g_rline.pos++;
	putcap("sc");
	ft_putstr( g_rline.cmd + g_rline.pos);
	putcap("rc");
	sz++;
	return (0);
}

int				count_str_num(void)
{
	unsigned int	i;

	i = 1;
	if ((ft_strlen(g_rline.cmd) + g_rline.prompt_len) > g_screen.ws_col)
	{
		while ((ft_strlen(g_rline.cmd) + g_rline.prompt_len) > g_screen.ws_col * i)
			i++;
	}
	return (i);
}

/*
** Till putcap("cd") we do the same as ctrl-k - clear the whole line
*/

int				insert_within_string_termcap(char c)
{
	// unsigned short	new_x;
	// unsigned short	new_y;
	unsigned short	end_x;
	unsigned short	end_y;

	if (position_relative(&end_x, &end_y, ft_strlen(g_rline.cmd) - 1))
		return (-1);
	position_cursor("ch", 0, g_rline.prompt_len);
	if (end_y > 1)
		position_cursor("UP", 0, end_y - 1);
	putcap("cd");
	// ft_putstr_fd(g_rline.cmd, 1);
	// if (ft_strlen(g_rline.cmd) + g_rline.prompt_len == g_screen.ws_col * g_rline.str_num)
	// 	putcap("sf");
	// if (position_relative(&new_x, &new_y, g_rline.pos + 1))
	// 	return (-1);
	// position_cursor("ch", 0, new_x);
	// if (new_x == g_screen.ws_col - 1 && new_y > 2)
	// 	position_cursor("DO", 0, 1);
	// else if (new_y > 2)
	// 	position_cursor("DO", 0, new_y - 1);
	// g_rline.flag = 1;
	
	// ft_putstr_fd(g_rline.cmd, 1);
	// if (ft_strlen(g_rline.cmd) + g_rline.prompt_len == g_screen.ws_col * g_rline.str_num)
	// 	putcap("sf");
	// // char			*swap;
	// unsigned short	new_x;
	// unsigned short	new_y;
	// // unsigned short	end_x;
	// // unsigned short	end_y;
	// // int i = 0;
	// // int len = ft_strlen(swap);

	// // swap = g_rline.cmd + g_rline.pos + 1;
	// // putcap("cd");
	// if (position_relative(&new_x, &new_y, g_rline.pos))
	// 	return (-1);

	// // if (position_relative(&new_x, &new_y, g_rline.pos + 1))
	// // 	return (-1);
	// // if (position_relative(&end_x, &end_y, ft_strlen(g_rline.cmd) - 1))
	// // 	return (-1);
	
	// position_cursor("ch", 0, g_rline.prompt_len);
	// if (new_x == g_screen.ws_col - 1 && new_y == 2)
	// 	position_cursor("UP", 0, 1);
	// else if (new_y > 2)
	// 	position_cursor("UP", 0, new_y - 1);
	// putcap("cd");
	// ft_putstr_fd(g_rline.cmd, 1);
	// if (ft_strlen(g_rline.cmd) + g_rline.prompt_len == g_screen.ws_col * g_rline.str_num)
	// 	putcap("sf");

	// // ft_putstr_fd(g_rline.cmd + g_rline.pos + 1, 1);
	// // if (ft_strlen(g_rline.cmd) + g_rline.prompt_len == g_screen.ws_col * g_rline.str_num)
	// // 	putcap("sf");
	
	// if (position_relative(&new_x, &new_y, g_rline.pos + 1))
	// 	return (-1);
	// position_cursor("ch", 0, new_x);
	// if (new_x == g_screen.ws_col - 1 && new_y == 2)
	// 	position_cursor("DO", 0, 1);
	// else if (new_y > 2)
	// 	position_cursor("DO", 0, new_y - 1);
	
	// // position_cursor("ch", 0, new_x);
	// // if (end_y - new_y)
	// // 	position_cursor("UP", 0, end_y - new_y);
	// // else if ((end_x == g_screen.ws_col - 1) && end_y - new_y == 0)
	// // 	position_cursor("UP", 0, 1);
	// g_rline.flag = 1;
	// // printf("pos %u - %u", new_x, new_y);
	// // printf("end %u - %u", end_x, end_y);
	return (0);
}