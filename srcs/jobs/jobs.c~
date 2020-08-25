/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:53:30 by hshawand          #+#    #+#             */
/*   Updated: 2020/08/24 16:14:55 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "jobs.h"

t_process		*find_process(t_job *j, pid_t child_pid)
{
	t_process *proc;

	proc = j->first_process;
	while (proc && proc->pid != child_pid)
		proc = proc->next;
	return (proc);
}

void			process_update(t_process *p, int status)
{
	WIFSTOPPED(status) ? (p->stopped = 1) :
		(p->completed = 1);
	p->status = status;
	exit_status_variables(WIFEXITED(status) ? WEXITSTATUS(status) : -1); //исправить для правильного возврата ошибки пайпа
	// возможно if (status != BTIN_ERROR)
	// exit_status_variables(WIFEXITED(status) ? WEXITSTATUS(status) : btin_return_exit_status());
}

int				parent(t_process *p, t_job *j, pid_t pid)
{
	p->pid = pid;
	if (g_is_interactive)
	{
		if (!j->pgid)
			j->pgid = pid;
		setpgid(pid, j->pgid);
	}
	return (0);
}

/*
** Forks given process in given job and provides pipe functionality
*/

int				fork_job(t_process *p, t_job *j, int *infl, int *outfl)
{
	pid_t	pid;
	int		mypipe[2];

	if (p->next)
	{
		if (pipe(mypipe) < 0)
			return (error_handler(PIPE_FAILED, "pipe creation failed"));
		*outfl = mypipe[1];
	}
	pid = ((!p->btin && g_path) || *infl != j->stdin || *outfl != j->stdout) ? fork() : 0;
	if (pid == 0)
	{
		p->next ? close(mypipe[0]) : 0;
		launch_process(p, j->pgid, (int[3]){*infl, *outfl, j->stderr}, j->fg);
	}
	else if (pid < 0)
		return (error_handler(FORK_FAILED, "fork creation failed"));
	else
		parent(p, j, (!p->btin || *infl != j->stdin ||
			*outfl != j->stdout) ? pid : getpid());
	*infl != STDIN_FILENO ? close(*infl) : 0;
	*outfl != STDOUT_FILENO ? close(*outfl) : 0;
	fd_list_process(p, CLOSE);
	*infl = mypipe[0];
	return (0);
}

/*
** Iterates through process list in given job, gives all necessary information
** to fork function and calls background/foreground processing function
*/

int				launch_job(t_job *j)
{
	t_process	*p;
	int			infile;
	int			outfile;

	infile = j->stdin;
	p = j->first_process;
	j->clean = j->fg ? 0 : 1;
	while (p)
	{
		g_path = !p->btin ? path_init(p->argv) : NULL;
		!p->next ? outfile = j->stdout : 0;
		if (fork_job(p, j, &infile, &outfile) == -1)
		{
			free(g_path);
			g_path = NULL;
			return (-1);
		}
		free(g_path);
		g_path = NULL;
		p = p->next;
	}
	bg_fg_wait(j);
	return (0);
}
