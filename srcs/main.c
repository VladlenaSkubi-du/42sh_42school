
#include "readline.h"

/*
** We take default xterm-256color - terminal
*/

int main()
{
    char    *cmd;
    char	*termtype;
	char	room_termtype[2];

    //сделать вход для heredoc, если heredoc, то readline немного другой
    if (isatty(STDIN_FILENO))
    {
        termtype = getenv("TERM");
        if (termtype == NULL)
            termtype = "xterm-256color";
        tgetent(room_termtype, termtype);
        // if (tgetent(room_termtype, termtype) != 1)
        //     readline_simple();
    }
    if(!(cmd = readline()))
    {
        ft_putendl_fd("Something has happend", 2);
        return (1);
    }
    printf("\n%s\n", cmd);
    free(cmd);
    return (0);
}