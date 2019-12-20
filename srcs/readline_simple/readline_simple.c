/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_simple.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 15:49:40 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/20 17:53:33 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int				make_sctrl_e(void)
{
	return (0);
}

int				make_sctrl_a(void)
{
	return (0);
}

int				sdelete_proc(void)
{
	
	return (0);
}

int				sbackspace_proc(void)
{
	return (0);
}

int				sstr_edit(char *swap, char add)
{
	int		i;
	int		len;

	i = -1;
	len = ft_strlen(swap);
	if (add > 0)
	{
		while (swap[++i])
			g_rline.cmd[g_rline.pos + 1 + i] = swap[i];
		write(STDOUT_FILENO, &add, 1);
		write(STDOUT_FILENO, swap, len);
		while (len--)
			write(STDOUT_FILENO, "\033[D", 3);
	}
	else
	{
		while (swap[++i])
			g_rline.cmd[g_rline.pos + i] = swap[i];
		g_rline.cmd[g_rline.pos + i] = '\0';
		write(STDOUT_FILENO, swap, len);
		write(STDOUT_FILENO, " ", 1);
		while (len-- >= 0)
			write(STDOUT_FILENO, "\033[D", 3);
	}
	return (0);
}

int				sstr_del_symbol(void)
{
	char	*swap;

	swap = NULL;
	if (g_rline.pos == 0)
		return (bell_sound());
	swap = ft_strdup(g_rline.cmd + g_rline.pos + 1);
	sstr_edit(swap, -1);
	free(swap);
	return (0);
}

int				sstr_add_symbol(char add)
{
	char	*swap;
	
	swap = NULL;
	if (ft_strlen(g_rline.cmd) == g_screen.ws_col)
		return (bell_sound());
	swap = ft_strdup(g_rline.cmd + g_rline.pos);
	g_rline.cmd[g_rline.pos] = add;
	if (swap != NULL)
		sstr_edit(swap, add);
	g_rline.pos++;
	free(swap);
	return (0);
}

int				schar_add(char c)
{
	static size_t	sz_max = CMD_SIZE + 1;
	static size_t	sz = 0;

	if (sz >= sz_max - 1)
	{
		g_rline.cmd = (char *)ft_realloc(g_rline.cmd, sz_max, sz_max,
			sz_max + CMD_SIZE);
		sz_max += CMD_SIZE;
	}
	sz++;
	g_rline.cmd_buff_len = sz_max;
	sstr_add_symbol(c);
	return (0);
}

int					sescape_init(void)
{
	char			*seq_base[SESC_NUM];

	seq_base[0] = "[C";
	seq_base[1] = "[A";
	seq_base[2] = "[D";
	seq_base[3] = "[B";
	return (sescape_check(seq_base));
}

int					sreadline_choice(char sy)
{
	if (sy == '\033')
		sescape_init();
	else if (ft_isprint(sy))
		schar_add(sy);
	else if (sy == '\004')
		sdelete_proc();
	else if (sy == 127 || sy == '\010')
		sbackspace_proc();
	else if (sy == '\001')
		make_sctrl_a();
	else if (sy == '\005')
		make_sctrl_e();
	return (0);
}

char				*readline_simple(void)
{
	char			c;

	init_readline();
	if (set_noncanonical_input() == -1)
	{
		ft_putendl_fd("Terminal can't be changed", 2);
		ft_putendl_fd("Use non-interactive shell", 2);
		return (NULL);
	}
	main_promt(); //сделать условие
	while (read(STDIN_FILENO, &c, 1) && c != '\n')
	{
		if (ioctl(1, TIOCGWINSZ, &g_screen))
		{
			ft_putendl_fd("Can't get terminal dimensions", 2);
			return (NULL);
		}
		sreadline_choice(c);
	}
	if (reset_canonical_input())
		exit(1);
	return (g_rline.cmd);
}