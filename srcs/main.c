/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 22:27:07 by sschmele          #+#    #+#             */
/*   Updated: 2020/09/01 21:39:13 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

int				main(int argc, char **argv)
{
	int			status;

	status = 0;
	create_env();
	if (argc > 1)
	{
		status = check_shell_options(argv);
		return (status);
	}
	start_history();
	hashtable_init();
	init_readline();
	g_prompt.prompt_func = main_prompt;
	interactive_shell();
	return (0);
}

/*
** First we check if 42sh program was launched in
** the background. We compare the process group that
** is considered as a controlling terminal owner with
** the pid of the group we are in. If controlling terminal
** does not belong to our group - we stop our group with
** SIGTTIN signal. After we get back to the foreground,
** we continue the work as thought we were launched in the
** foreground from the very beginning.
** We start history, because it exists only in the interactive
** mode.
** After changing the terminal to non-canonical mode, and
** signal handler to the one for readine, we look for
** terminal describtion for termcap library usage.
*/

int				interactive_shell(void)
{
	char		*termtype;
	char		room_termtype[10];
	int			tmp;
	pid_t		group_pid;

	tmp = 0;
	btin_alias_init(NULL, NULL, SAVE);
	group_pid = getpgrp();
	if (tcgetpgrp(STDIN_FILENO) != group_pid)
		kill(group_pid, SIGTTIN);
	while (1)
	{
		signals_reroute(1);
		check_terminal();
		g_prompt.prompt_func();
		termtype = getenv("TERM");
		termtype = (termtype == NULL) ? "xterm-256color" : termtype;
		tmp = tgetent(room_termtype, termtype);
		start_readline42(tmp);
		jobs_clean();
		ft_bzero(room_termtype, 10);
	}
	return (0);
}

int				noninteractive_shell(char **argv)
{
	char		*cmd;
	int			status;

	preparation_noninteractive();
	cmd = ft_strdup(argv[0]);
	parser(cmd);
	status = ft_atoi(find_env_value("?"));
	clean_everything();
	exit(status);
}

int				preparation_noninteractive(void)
{
	int			li;
	int			sy;
	
	li = find_in_variable(&sy, "42SH_NONINTERACTIVE");
	g_envi[li][sy] = '1';
	g_prompt.prompt_func = NULL;
	return (0);
}
