#ifndef READLINE_H
# define READLINE_H

# include <unistd.h>
# include <stdlib.h>
# include <curses.h>
# include <term.h>
# include <termios.h>

#include <stdio.h> //DELETE

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

struct termios		g_tty;
struct termios		g_backup_tty;

/*
** File readline.c
*/

char				*readline(void);

/*
** File terminal_input_changes.c
*/

int					set_noncanonical_input(void);
int					reset_canonical_input(void);
int					back_to_noncanonical_input(void);

/*
** File termcap_usage.c
*/

int					putcap(char *cap);
int					printc(int c);

#endif
