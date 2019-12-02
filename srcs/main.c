
#include "readline.h"

int main()
{
    char    *cmd;

    //сделать вход для heredoc, если heredoc, то readline немного другой
    if(!(cmd = readline()))
    {
        ft_putendl_fd("Something has happend", 2);
        return (1);
    }
    printf("\n%s\n", cmd);
    free(cmd);
    return (0);
}