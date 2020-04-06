#include "shell42.h"
#include "shell42.h"

/*
** First we check if 42sh program was launched in
** the background. We compare the process group that
** is considered as a controlling terminal owner with
** the pid of the group we are in. If controlling terminal
** does not belong to our group - we stop our group with
** SIGTTIN signal. After we get back to the foreground,
** we continue the work as thought we were launched in the
** foreground from the very beginning.
*/

int				interactive_shell(void)
{
	char		*termtype;
	char		room_termtype[100];
	int			tmp;
	pid_t		group_pid;

	group_pid = getpgrp();
	// if (tcgetpgrp(STDIN_FILENO) != group_pid) //вылетает дебаггер временно выключено
	// 	kill(group_pid, SIGTTIN);
	start_history();
	while (1)
	{
		init_readline();
		signals_reroute(1);
		check_terminal();
		g_prompt.prompt_func();
		termtype = getenv("TERM");
		termtype = (termtype == NULL) ? "xterm-256color" : termtype;
		tmp = tgetent(room_termtype, termtype);
		start_readline42(tmp);
		ft_bzero(room_termtype, 100);
	}
	return (0);
}

/*
** Here we check the terminal (we already know that
** our group owns a controlling terminal) and set it
** to the non-canonical mode
*/

int				check_terminal(void)
{
	if (!isatty(STDIN_FILENO))
	{
		error_handler(TERMINAL_EXISTS, NULL);
		exit(TERMINAL_EXISTS);
	}
	if (set_noncanonical_input() == -1)
	{
		error_handler(TERMINAL_TO_NON, NULL);
		clean_readline42();
		clean_everything();
		exit(TERMINAL_TO_NON);
	}
	return (0);
}

/*
** If we did not get describtion of the terminal
** or there is no termcap library, we are still able
** to make the line alterable with readline-simple
** And from here we go to parser in the interactive mode
*/

int				start_readline42(int tmp)
{
	char		*final;

	if (tmp != 1)
		readline_simple();
	else
		readline();
	reset_canonical_input();
	check_menu();
	final = finalize_cmd(g_rline.cmd);
	clean_readline42();
	signals_reroute(2);
	parser(final);
	return (0);
}

char			*finalize_cmd(char *cmd)
{
	char		*out;
	char		*tmp;

	tmp = ft_strtrim(cmd);
	if (ft_strlen(tmp) == 0)
	{
		out = ft_xmalloc(1);
		free(tmp);
		return (out);
	}
	if (g_rline.cmd_len == 0)
		out = ft_strdup(cmd);
	else
		out = ft_strjoin(cmd, "\n");
	free(tmp);
	return (out);
}
