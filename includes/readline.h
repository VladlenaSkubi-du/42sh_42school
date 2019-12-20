/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:03:22 by sschmele          #+#    #+#             */
/*   Updated: 2019/12/20 13:23:06 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

# include <unistd.h>
# include <stdlib.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <sys/ioctl.h>

# include <stdio.h> //DELETE

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "ft_select.h"

# define CMD_SIZE 10

/*
** @cmd is a command string printed by the user
** @pos - position of the cursor in the command-string
** @str_num - number of lines the command-string consists of
** @prompt_len - length of the prompt (invitation to enter the command)
*/

typedef struct					s_rline
{
	char						*cmd;
	size_t						pos;
	size_t						str_num;
	size_t						prompt_len;
	size_t						cmd_buff_len;
	short						flag;
}								t_rline;

typedef struct					s_action_stack
{
	char						*cmd_b;
	size_t						pos_b;
	size_t						num_b;
	struct s_action_stack		*next;
	struct s_action_stack		*prev;
}								t_action_stack;

t_rline							g_rline;
struct winsize					g_screen;
struct termios					g_tty;
struct termios					g_backup_tty;

/*
** File readline.c - the beginning of the work with readline
*/

char							*readline(void);
void							init_readline(void);
int								readline_choice(char sy);

/*
** File prompts.c
*/

int								main_promt(void);
int								other_prompts(char flag);

/*
** File terminal_input_changes.c
*/

int								set_noncanonical_input(void);
int								reset_canonical_input(void);
int								back_to_noncanonical_input(void);

/*
** File termcap_usage.c - library of functions to use termcap easily
*/

int								putcap(char *cap);
int								printc(int c);
int								position_cursor(char *cap, int x, int y);

/*
** File str_edit.c - universal functions for changing the main command-string
** and dealing with other global-parameters of the command string
*/

int								char_add(char c);
int								str_shift(char *str, int shift);
int								insert_char(char c);
int								count_str_num(void);

/*
** File escape.c - router to the functions performing actions with
** escape-sequences
*/

int								escape_init(void);
int								escape_check(char **seq_base);
int								incorrect_sequence(void);
int								sequence_process(int sequence_num);

/*
** File ctrl_key.c
*/

int								ctrl_key(char sy);
int								ctrl_process(char *ctrl_base, char sy);
int								ctrl_call(size_t call_num);

/*
** File cursor_position.c - operations to get the termcap cursor postion
** and move it after actions
*/

unsigned int					on_which_line(size_t cmd_pos,
									unsigned short col);
int								position_relative(unsigned short *x,
									unsigned short *y, size_t analyse);
int								move_cursor_back_after_print(short flag);
int								move_cursor_from_old_position(size_t pos_old,
									char direction);

/*
** File undo_call.c
*/

int								make_ctrl_x(void);
int								undo_wrap(void);
int								undo_redraw(size_t pos_old);

/*
** File undo.c
*/

int								undo(int mode);
void							action_pull(t_action_stack **start,
									size_t *num);
void							action_alloc_management(t_action_stack *start,
									int mode);
int								action_add(t_action_stack **start,
									t_action_stack **end, size_t *num);
t_action_stack					*action_new(void);

/*
** Actions ____________________________________________________________________
*/

/*
** File non_printable.c
*/

int								backspace_process(void);
int								delete_process(void);

/*
** File arrow_keys.c
*/

int								key_right_proc(void);
int								key_up_proc(void);
int								key_left_proc(void);
int								key_down_proc(void);

/*
** File esc_word_proc.c
*/

int								word_left_proc(void);
int								word_right_proc(void);
int								esc_d(void);
int								esc_r(void);
char							*save_word(size_t *i, char *cmd, size_t pos);

/*
** File esc_t.c - continuation in esc_word_proc.c
*/

int								esc_t(void);
int								esc_t_first_left(char flag, size_t pos_back);
int								esc_t_need_left(char *word_first, size_t fi,
									char *end);
int								esc_t_need_right(char *word_first, size_t fi,
									char *end);
int								esc_t_len_pos(char *word_first, size_t fi,
									size_t pos_back);
char							*save_end(size_t pos_back);

/*
** File ctrl_kwuae.c
*/

int								make_ctrl_k(void);
int								make_ctrl_u(void);
int								make_ctrl_a(void);
int								make_ctrl_e(void);
int								make_ctrl_w(void);

/*
** File ctrl_tl.c
*/

int								make_ctrl_t(void);
int								make_ctrl_t_begend(size_t len);
int								make_ctrl_l(void);

/*
** File print_readline_help.c
*/

void							print_readline_help(void);
void							printf_readline_help_further(void);

/*
** Should be included in libft ________________________________________________
*/

void							*ft_realloc(void *subj, size_t len_subj,
								size_t len, size_t len_needed);
void							*ft_xmalloc(size_t size);
void							swap_chars(char *cmd, int b, int a);
void							swap_ints(int *a, int *b);
int								ft_issign(char c);

#endif
