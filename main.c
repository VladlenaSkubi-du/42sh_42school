#include <stdio.h>
#include "readline.h"

int main()
{
    char    *cmd;

    if(!(cmd = readline()))
        return (1);
    printf("\n%s\n", cmd);
    free(cmd);
}