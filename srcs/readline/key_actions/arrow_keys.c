
#include "shell42.h"
#include "readline.h"

/*
** Problems here:
** 1) prompt exists only in the first line
** 2) if there are several lines and we stay on the most right position and push
** "move right" - we need to jump to the beginning of the next line;
** if we are on the most left position and push "move left" - we need to
** jump to the end of the previous line - so we always need to count on
** what line we are standing on and in which x-position according to
** the terminal's width
** 3) as one of the user functions beeps if the action is not possible
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

/*
** Clears the current line and inserts the previous line from
** history. History buffer is always len + 1 + 1 size where
** one is for NULL-line and one is for the current line to be saved
*/

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
	(g_rline.cmd[0]) ? clear_whole_line() : 0;
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

/*
** Clears the current line and inserts the following line from
** history. History buffer is always len + 1 + 1 size where
** one is for NULL-line and one is for the "current" line to be saved
** when the counter reaches g_hist.last + 1 value that means that
** we reached the current cmd-line that was temporarily saved
*/

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
	(g_rline.cmd[0]) ? clear_whole_line() : 0;
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
