/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:03:22 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/29 17:12:56 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

# include <curses.h>
# include <term.h>
# include <termios.h>
# include <sys/ioctl.h>

# include <stdio.h> //DELETE

# include "readline_simple.h"
# include "get_next_line.h" //If not used, delete

# define CMD_SIZE	5
# define TAB		0x1

/*
** @t_rline is for the whole readline part:
**
** @cmd is a command string printed by the user
** @pos - position of the cursor in the command-string
** @str_num - number of lines the command-string consists of
** @prompt_len - length of the prompt (invitation to enter the command)
** @cmd_buff_len - buffer of the cmd-line
** (can grow, after printing "Enter" is freed)
** @flag - the "working" variable
*/

typedef struct					s_rline
{
	char						*cmd;
	size_t						cmd_len;
	size_t						pos;
	size_t						str_num;
	size_t						prompt_len;
	size_t						cmd_buff_len;
	short						flag;
}								t_rline;

/*
** @t_action_stack is for the "ctrl-x ctrl-u" action:
**
** @cmd_b - the command string printed by the user before
** the last change (last action)
** @pos_b - position of the cursor in the command-string before
** the last change (last action)
** @num_b - number of lines the command-string consisted of before
** the last change (last action)
*/

typedef struct					s_action_stack
{
	char						*cmd_b;
	size_t						pos_b;
	size_t						num_b;
	struct s_action_stack		*next;
	struct s_action_stack		*prev;
}								t_action_stack;

/*
** @t_complition is for the auto-completion part
**
** @buffer - the menu-buffer (all the options for completion)
** @buf_lines - how many lines the menu buffer consists of after
** allocations into columns and lines
** @buf_width - the length of each buffer line (including all tabs)
** @word_len - the maximal length of the word with the tab inscluded,
** according to which alignment is done (as in ls-program)
** @word_nb - the number of menu-options
** @i - counter
*/

typedef struct					s_completion
{
	char						**buffer;
	int							buf_lines;
	int							buf_width;
	int							word_len;
	int							word_nb;
	size_t						i;
}								t_completion;

t_rline							g_rline;
// t_prompt						g_prompt;
struct winsize					g_screen;
// struct termios					g_tty; //TODO убрать, если
struct termios					g_backup_tty;

/*
** File start_readline42.c
*/

int								interactive_shell(void);
int								start_readline42(int tmp);
char							*finalize_cmd(char *cmd);
int								clean_readline42(void);
int								init_prompt(char flag); //TODO DELETE

/*
** File readline.c - the beginning of the work with readline
*/

char							*readline(void);
void							init_readline(void);
int								readline_choice(char sy);

/*
** File prompts.c
*/

int								main_prompt(void);
int								dquote_prompt(void);
int								heredoc_prompt(void);
int								subshell_prompt(void);
int								other_prompt(void);

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
** File undo_yank_call.c
*/

int								make_ctrl_x(void);
int								undo_wrap(void);
int								undo_redraw(size_t pos_old);
int								make_ctrl_y_wrap(void);

/*
** File undo.c
*/

int								undo(int mode);
void							action_pull(t_action_stack **start,
									size_t *num);
void							action_alloc_management(t_action_stack **start,
									int mode);
int								action_add(t_action_stack **start,
									t_action_stack **end, size_t *num);
t_action_stack					*action_new(void);

/*
** Actions in the folder key_actions___________________________________________
*/

/*
** File cut_keys.c
*/

int								backspace_process(void);
int								delete_till_compl(size_t len_compl,
									size_t delete);
int								delete_process(void);
int								route_exit(void);
int								esc_r(void);

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
char							*save_word(size_t *i, char *cmd, size_t pos);
char							*save_end(size_t pos_back);

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

/*
** File ctrl_kwuae.c
*/

int								make_ctrl_k(void);
int								make_ctrl_u(void);
int								make_ctrl_a(void);
int								make_ctrl_e(void);
int								make_ctrl_w(void);

/*
** File ctrl_tly.c
*/

int								make_ctrl_t(void);
int								make_ctrl_t_begend(size_t len);
int								make_ctrl_l(void);
int								make_ctrl_y(int mode, char *yank);
int								yank_insert(char *yank_str,
									size_t len_yank);

/*
** Folder auto_completion ______________________________________________________
*/

/*
** File start_completion.c
*/

int								auto_completion(void);
char							**route_menu_receipt(char *tech_line,
									size_t tech_len, size_t *total,
									int *max_len);
int								insert_word_compl(void);
int								check_menu(void);

/*
** File analyse_line.c
*/

char							*get_techline_compl(char *complete,
									size_t len);
int								analyse_techline_compl(char *compl,
									char *tech_line,
									size_t len, int *pool);
int								pass_symbols(char *compl, char *tech,
									int i, int *pool);
int								route_to_pools(char *tech, int i,
									int *pool);
int								route_to_arguments(char *compl,
									int i, int *pool);

/*
** File menu_receipt.c
*/

char							**get_variables(char *complete,
									size_t *total, int *max_len);
t_path							*fill_tree_with_variables(char *complete,
									size_t *total, size_t len);
char							**get_arguments(char **complete,
									size_t *total, int *max_len);
t_path							*fill_tree_with_arguments(char *path,
									char *complete, size_t *total);

/*
** File front_part.c
*/

int								print_menu(size_t pos_back, char **menu,
									size_t total, int max_len);
int								after_big_menu(size_t pos_back,
									unsigned short len_x);
int								print_menu_buf_after_insert(size_t pos_back);
int								clean_menu(void);
int								clean_menu_buf(void);

/*
** File question_if_many.c and also a small function (because of norm)
*/

int								ask_output(size_t total, int buf_lines,
									size_t pos_back, unsigned short len_x);
int								count_comment_len(unsigned short *total_len,
									unsigned short *lines_len,
									size_t total, int buf_lines);
int								clean_output_question(int from, size_t pos_back,
									unsigned short len, unsigned short len_x);
int								clean_strings_compl(char *compl,
									char *tech_line, int flag);

/*
** File path_processing_compl.c
*/

char							*find_path_compl(char *compl, int tmp);
char							*path_parse_compl(void);

/*
** File cursor_position_completion.c
*/

int								position_cursor_for_menu(size_t len);
int								position_cursor_after_menu_back
									(unsigned short len_x, int buf_lines,
									size_t pos_back, size_t len);

/*
** File output_buffer.c
*/

t_completion					menu_buf_init(size_t total, int max_len);
int								buffer_col_print(char *add,
									t_completion *menu_buf);
void							buffer_col_calc(t_completion *menu_buf);
void							buffer_col_finish(t_completion *menu_buf);
void							buf_add(char *str, size_t size);

/*
**_____________________________________________________________________________
*/

/*
** File print_readline_help.c
*/

void							print_help(short flag);
void							print_readline_help(short flag,
									short undo, char *space);
void							printf_readline_help_ccp(short flag,
									short undo, char *space);
void							print_readline_help_other(short flag,
									short undo, char *space);

#endif
