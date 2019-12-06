#ifndef READLINE_H
# define READLINE_H

# include <unistd.h>
# include <stdlib.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <sys/ioctl.h>

#include <stdio.h> //DELETE

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

# define CMD_SIZE 1024

typedef struct		s_rline
{
	char			*cmd;
	size_t			pos;
	size_t			str_num;
	size_t			prompt_len;
}					t_rline;

t_rline				g_rline;
struct termios		g_tty;
struct termios		g_backup_tty;

/*
** File readline.c
*/

char				*readline(void);
int					display_promt(void);
int					readline_choice(char sy);

/*
** File terminal_input_changes.c
*/

int					set_noncanonical_input(void);
int					reset_canonical_input(void);
int					back_to_noncanonical_input(void);

/*
** File ctrl_str_changes.c
*/

int					ctrl_key(char sy);
int					make_ctrl_k(void);
int					make_ctrl_t(void);

/*
** File str_edit.c
*/
void				backspace_process(void);
int					char_add(char c);
int					str_shift(char *str, int shift);
int					count_str_num(void);

/*
** File termcap_usage.c
*/

int					putcap(char *cap);
int					printc(int c);
int					position_cursor(char *cap, int x, int y);

/*
** File escape.c
*/

int					escape_init(void);
int					escape_check(char **seq_base);
int					incorrect_sequence(void);
int					sequence_process(int sequence_num);


/*
** File arrow_keys.c
*/

int					key_right_proc(void);
int					key_up_proc(void);
int					key_left_proc(void);
int					key_down_proc(void);

/*
** Should be included in libft ________________________________________________________________________________________
*/

/*
** File ft_realloc.c
*/

void				*ft_realloc(void *subj, size_t len_subj,
						size_t len, size_t len_needed);

/*
** File ft_xmalloc.c
*/

void				*ft_xmalloc(size_t size);


/*
** File swap_chars.c
*/

void				swap_chars(char *cmd, int b, int a);

#endif
