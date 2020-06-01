
#include "shell42.h"
#include "readline.h"

/*
** Problems here:
** 1) prompt exists only in the first line
** 2) if there are several lines and we stay on the most right position and push
** "move right" - we need to position in the beginning of the next line;
** if we are on the most left position and push "move left" - we need to
** position in the end of the previous line - so we always need to count on
** what line we are standing on
** 3) position is counted starting from zero - sometimes there is minus 1 when
** we compare with the number of columns
**
** by 'while (g_rline.pos + g_prompt.prompt_len > (sz.ws_col - 1) * i)' we get
** the line the cursor (== position) is on
*/

int		key_right_proc(void)
{
	if (g_rline.pos < 0 || g_rline.pos >= g_rline.cmd_len)
		return (incorrect_sequence());
	if (front_move_one_char_right(g_rline.pos_x))
		return (incorrect_sequence());
	g_rline.pos++;
	return (0);
}

int		key_left_proc(void)
{
	if (g_rline.pos <= 0)
		return (incorrect_sequence());
	if (front_move_one_char_left(g_rline.pos_x))
		return (incorrect_sequence());
	g_rline.pos--;
	return (0);
}

int		key_up_proc(void)
{
	int				i;
	int				len;

	check_after_line();
	if (g_hist.counter <= 0)
	{
		g_hist.counter = 0;
		return (0);
	}
	key_up_proc_processing();
	(g_rline.cmd[0]) ? esc_r() : 0;
	g_hist.counter--;
	i = -1;
	len = ft_strlen(g_hist.hist[g_hist.counter]);
	if (len > 0 && g_hist.hist[g_hist.counter][len - 1] == '\n')
		len--;
	while (++i < len)
		char_add_without_undo(g_hist.hist[g_hist.counter][i], NULL);
	return (0);
}

int		key_up_proc_processing(void)
{
	if (g_hist.counter > g_hist.last)
	{
		g_hist.counter = g_hist.last + 1;
		(g_rline.cmd[0]) ?
			g_hist.hist[g_hist.counter] = ft_strdup(g_rline.cmd) : 0;
	}
	if (g_rline.cmd[0] && g_hist.counter <= g_hist.last)
	{
		free(g_hist.hist[g_hist.counter]);
		g_hist.hist[g_hist.counter] = ft_strdup(g_rline.cmd);
	}
	return (0);
}

int		key_down_proc(void)
{
	int				i;
	int				len;

	check_after_line();
	if (g_rline.cmd[0] && g_hist.counter <= g_hist.last)
	{
		free(g_hist.hist[g_hist.counter]);
		g_hist.hist[g_hist.counter] = ft_strdup(g_rline.cmd);
	}
	(g_rline.cmd[0]) ? esc_r() : 0;
	if (g_hist.counter >= g_hist.last)
		g_hist.counter = g_hist.last;
	g_hist.counter++;
	i = -1;
	len = ft_strlen(g_hist.hist[g_hist.counter]);
	if (len > 0 && g_hist.hist[g_hist.counter][len - 1] == '\n')
		len--;
	while (++i < len)
		char_add_without_undo(g_hist.hist[g_hist.counter][i], NULL);
	if (g_hist.hist[g_hist.counter] && g_hist.counter == g_hist.last + 1)
	{
		free(g_hist.hist[g_hist.counter]);
		g_hist.hist[g_hist.counter] = (char*)NULL;
	}
	return (0);
}
