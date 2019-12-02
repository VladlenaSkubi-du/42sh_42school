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
char				*g_cmd;

/*
** File readline.c
*/

char				*readline(void);
int					display_promt(void);
int					readline_choice(char sy, size_t pos);

/*
** File terminal_input_changes.c
*/

int					set_noncanonical_input(void);
int					reset_canonical_input(void);
int					back_to_noncanonical_input(void);

/*
** File ctrl_str_changes.c
*/

int					ctrl_key(char sy, size_t pos);

/*
** File str_edit.c
*/
void				backspace_process(size_t *pos);
int					char_add(char c, size_t *pos);
int					str_shift(char *str, int shift);

/*
** File termcap_usage.c
*/

int					putcap(char *cap);
int					printc(int c);

/*
** File ft_realloc.c
*/

void				*ft_realloc(void *subj, size_t len_subj,
						size_t len, size_t len_needed);

/*
** File ft_xmalloc.c
*/

void				*ft_xmalloc(size_t size);

#endif