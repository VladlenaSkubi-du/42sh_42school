
#include "shell42.h"
#include "jobs.h"

/* Put job j in the foreground.  If cont is nonzero,
   restore the saved terminal modes and send the process group a
   SIGCONT signal to wake it up before we block.  */


/* STOP! We are doing this through signals! */

void	wait_for_job (job *j)
{
	while (!job_is_stopped (j, 0) && !job_is_completed (j));
}

void	put_job_in_foreground (job *j, int cont)
{
	/* Put the job into the foreground.  */
	j->fg = 1;
	j->clean = 0;
	tcsetpgrp (STDIN_FILENO, j->pgid);
	/* Send the job a continue signal, if necessary.  */
	if (cont)
	{
		tcsetattr (STDIN_FILENO, TCSADRAIN, &j->tmodes);
		if (kill (- j->pgid, SIGCONT) < 0)
			perror ("kill (SIGCONT)");
    }
	/* Wait for it to report.  */
	wait_for_job (j);
	/* Put the shell back in the foreground.  */
	tcsetpgrp (STDIN_FILENO, g_shell_pgid);
	/* Restore the shell’s terminal modes.  */
	tcgetattr (STDIN_FILENO, &j->tmodes);
	tcsetattr (STDIN_FILENO, TCSADRAIN, &g_shell_tmodes);
	j->clean = 1;
	job_is_completed(j) && free_job(j);
}

/* Put a job in the background.  If the cont argument is true, send
   the process group a SIGCONT signal to wake it up.  */

void	put_job_in_background (job *j, int cont)
{
	/* Send the job a continue signal, if necessary.  */
	j->fg = 0;
	j->clean = 1;
	ft_printf("[%d] %d\n", j->jid, j->pgid);
	if (cont)
		if (kill (-j->pgid, SIGCONT) < 0)
			perror ("kill (SIGCONT)");
}

int		bg_fg_wait(job *j)
{
	if (!g_is_interactive)
		wait_for_job (j);
	else if (j->fg)
		put_job_in_foreground (j, 0);
	else
		put_job_in_background (j, 0);
	return (0);
}
