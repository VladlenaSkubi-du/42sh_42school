
#ifndef READLINE_H
# define READLINE_H

# include "readline_simple.h"

# define TERMCAP_SIZE 		20
# define CMD_SIZE			100

# define TAB				0x1
# define NEW_LINE_SY		0x2
# define NEW_LINE_TE		0x4
# define AFTER_LINE			0x8
# define AFTER_LINE_HIST	0x10
# define PROMPTLEN_ZERO		0x20

# define RED				"\033[31m"
# define ORANGE				"\033[38;5;208m"
# define YELLOW				"\033[33m"
# define GREEN				"\033[32m"
# define BLUE				"\033[36m"
# define PURPLE				"\033[35m"
# define DEFAULT			"\033[0m"

/*
** Structures
** ____________________________________________________________________________
*/

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
	int							cmd_len;
	int							pos;
	int							pos_x;
	int							pos_y;
	int							str_num;
	int							cmd_buff_len;
	int							flag;
}								t_rline;

/*
** The main termcap codes used
*/

typedef struct					s_cap
{
	char						sf[TERMCAP_SIZE];
	char						le[TERMCAP_SIZE];
	char						nd[TERMCAP_SIZE];
	char						up[TERMCAP_SIZE];
	char						dow[TERMCAP_SIZE];
	char						cd[TERMCAP_SIZE];
	char						cr[TERMCAP_SIZE];
}								t_cap;

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

typedef struct					s_compl_output
{
	char						**buffer;
	int							buf_lines;
	int							buf_width;
	int							word_len;
	int							word_nb;
	size_t						i;
}								t_compl_output;

/*
** @g_tablevel is a counter according to that we complete this or that line
** from the g_menu
** @g_complete - is a string, according to which we search
** options for completion. Can be empty if TAB is pushed before any other key
** @g_menu - the full menu for completion, all the possible options
*/

typedef struct					s_compl
{
	char						*to_compl;
	int							len_tocompl;
	char						**menu;
	int							total;
	int							tablevel;
	int							to_del;
	t_compl_output				menu_buffer;
}								t_compl;

/*
** Globals
** ____________________________________________________________________________
*/

t_rline							g_rline;
struct winsize					g_screen;
t_cap							g_cap;
struct termios					g_backup_tty;
t_compl							g_compl;

/*
** Functions
** ____________________________________________________________________________
*/

/*
** File start_readline42.c
*/

void							init_readline(void);
void							bzero_readline(void);;
int								start_readline42(int tmp);
char							*finalize_cmd(char *cmd);

/*
** File terminal_input_changes.c
*/

int								check_terminal(void);
int								mf_protection(void);
int								set_noncanonical_input(void);
int								reset_canonical_input(void);
// int								back_to_noncanonical_input(void); //DELETE

/*
** File termcap_usage.c - library of functions to use termcap easily
*/

int								putcap(char *cap);
int								printc(int c);
int								position_cursor(char *cap, int x, int y);
int								init_termcap(void);

/*
** File readline.c - the beginning of the work with readline
*/

int								readline(void);
int								readline_choice(char sy);
int								route_exit(void);
int								incorrect_sequence(void);
int								check_after_line(void);

/*
** File prompts.c
*/

int								main_prompt(void);
int								dquote_prompt(void);
int								heredoc_prompt(void);
int								other_prompt(void);
int								count_prompt_len(void);

/*
** File prompts_other.c
*/

int								pipe_prompt(void);
int								subshell_prompt(void);
int								cursh_prompt(void);
int								cmdandor_prompt(void);

/*
** File rline_cmd_processing.c
*/

int								char_add(char c, char *color);
int								char_add_without_undo(char c, char *color);
int								insert_char(char c, char *color);
int								front_insert_cmd_till_the_end(int str_num_print);
int								front_set_cursor_jmp(int *pos, int *pos_x,
									int *pos_y, int flag);

/*
** File front_cursor_changes.c
*/

int								front_move_one_char_right(int pos_x);
int								front_move_one_char_left(int pos_x);
int								front_insert_by_letters(char *str, int *pos_x);
int								count_x_position_new_line(int nl_pos);
int								move_cursor_from_old_position(int pos_old,
									char direction);

/*
** File front_insertions.c
*/

int								front_insert_one_char(char c, int pos_x,
									char flag, char *color);
int								front_insert_if_newline(int *pos_x, int *pos_y,
									int *str_num, int *flag);
int								front_insert_if_terminal(int *pos_x,
									int *pos_y, int *flag);
int								front_insert_if_line(int *pos_x,
									int *str_num, int *flag);
int								front_write_one_char(char c, char *color);

/*
** File cursor_positioning.c
*/

int								position_cursor_after_line(int len);
int								clean_after_line(void);
int								clear_whole_line(void);

/*
** File colors.c
*/

char							*colors_process(int sequence_num);

/*
** File escape.c - router to the functions performing actions with
** escape-sequences
*/

int								escape_init(void);
int								escape_check(char **seq_base);
int								sequence_process(int sequence_num);

/*
** File ctrl_key.c - router to the functions performing actions with
** ctrl-sequences
*/

int								ctrl_key(char sy);
int								ctrl_process(char *ctrl_base, char sy);
int								ctrl_call(int call_num);
int								undo_wrap(void);
int								make_ctrl_x(void);

/*
** File undo.c
*/

int								undo(int mode);
void							action_pull(t_action_stack **start,
									int *num);
void							action_alloc_management(t_action_stack **start,
									int mode);
int								action_add(t_action_stack **start,
									t_action_stack **end, int *num);
t_action_stack					*action_new(void);

/*
** Folder KEY_ACTIONS
** ____________________________________________________________________________
*/

/*
** File cut_keys.c
*/

int								backspace_process(void);
int								backspace_newline(char *swap, int len_swap);
int								delete_process(void);
int								delete_till_compl(int delete);
int								esc_r(void);

/*
** File arrow_keys.c
*/

int								key_right_proc(void);
int								key_up_proc(void);
int								key_up_proc_processing(void);
int								key_left_proc(void);
int								key_down_proc(void);

/*
** File ctrl_kult.c
*/

int								make_ctrl_k(void);
int								make_ctrl_u(void);
int								make_ctrl_l(void);
int								make_ctrl_t(void);
int								make_ctrl_t_begend(int len);

/*
** File cut_words_and_paste.c
*/

int								esc_d(void);
int								make_ctrl_w(void);
int								make_ctrl_p_wrap(void);
int								make_ctrl_p(int mode, char *yank);
int								paste_insert(char *yank_str);


/*
** File esc_word_proc.c
*/

int								word_left_proc(void);
int								word_left_onetwo_chars(void);
int								word_right_proc(void);
char							*save_word(int *i, char *cmd, int pos);
char							*save_end(int pos_back);

/*
** File jump_around.c
*/

int             				jump_up(void);
int             				jump_down(void);
int								make_ctrl_a(void);
int								make_ctrl_e(void);

/*
** File esc_t.c - continuation in esc_word_proc.c
*/

int								esc_t(void);
int								esc_t_first_left(char flag, int pos_back);
int								esc_t_need_left(char *word_first, int fi,
									char *end);
int								esc_t_need_right(char *word_first, int fi,
									char *end);
int								esc_t_len_pos(char *word_first, int fi);

/*
** File easter_egg.c
*/

int								kirill_lgbt(char sy);

/*
** Folder AUTO_COMPLETION
** ____________________________________________________________________________
*/

/*
** File start_completion.c
*/

int								auto_completion(void);
char							**route_by_prompts(int *total, int *max_len);
char							**route_menu_receipt(char *tech_line,
									int tech_len, int *max_len);
int								insert_word_compl(void);
int								insert_word_by_cases_compl(int *delete, int flag,
									char *menu_word, int compl_len);

/*
** File completion_processing.c
*/

int								init_completion(void);
int								clear_completion(int flag);
int								make_one_slash(char **final, int last_slash, char *compl);

/*
** File analyse_line_compl.c
*/

int								analyse_techline_compl(char *compl,
									char *tech_line, int len, int *pool);
int								pass_symbols_compl(char *compl, char *tech,
									int i, int *pool);
int								check_path_pool_three_compl(char *compl, char *tech,
									int *pool, int i);
int								route_to_pools(char *tech, int i,
									int *pool);

/*
** File menu_receipt_compl.c
*/

char							**get_variables(char *complete,
									int *total, int *max_len);
t_path							*fill_tree_with_variables(char *complete,
									int *total);
char							**get_arguments(char **complete,
									int *total, int *max_len);
char							*find_path_compl(char *compl, int tmp);
t_path							*fill_tree_with_arguments(char *path,
									char *complete, int *total);

/*
** File front_part_compl.c
*/

int								print_menu(int max_len);
int								print_menu_within_terminal(int pos_back,
									int len_x, int len_y);
int								print_menu_more_than_terminal(int pos_back,
									int len_x, int len_y);
int								print_menu_buf_after_insert(int pos_back);
int								position_cursor_after_menu_back(int len_x, int len_y,
									int buf_lines, int pos_back);

/*
** File question_if_many_compl.c and also a small function (because of norm)
*/

int								ask_output(int total, int buf_lines,
									int pos_back, int len_x);
int								print_question_compl(int *pos_x_com, int total,
									int buf_lines);
int								after_big_menu(int pos_back,
									int len_x, int len_y);
int								count_comment_len(int *find, int num);
int								clean_output_question(int from, int pos_back,
									int len, int len_x);

/*
** File output_buffer_compl.c
*/

t_compl_output					menu_buf_init(int total, int max_len);
int								buffer_col_print(char *add,
									t_compl_output *menu_buf);
void							buffer_col_calc(t_compl_output *menu_buf);
void							buffer_col_finish(t_compl_output *menu_buf);
void							buf_add(char *str, int size);

/*
** Folder HISTORY
** ____________________________________________________________________________
*/

/*
** File start_history.c
*/

int								start_history(void);
void            				init_history_buffer(int size);
char							*define_history_file(void);
int								add_to_history(char *cmd);
int								add_other_prompts_history(char *cmd,
									int flag);

/*
** File history_buffer_proc.c
*/

int								scroll_hist_buffer(int num);
int								save_hist_buffer(int fd);
int								check_if_histsize_changed(void);
char							**make_hist_buffer_smaller(int size);

/*
** File history_file_proc.c
*/

int								fill_hist_in_file(void);
int								insert_hist_in_file(int fd, int user_len);
int								open_hist_file(int user_len, char *path);
int                 			read_hist_from_file(int fd);

/*
** File history_processing.c
*/

int                 			delete_last_history_element(void);

/*
** File front_part_hist.c
*/

int								make_ctrl_r_history(void);
char							*get_the_answer_hist(int *len);
int								insert_valid_sy_hist(char c,
									int *len, char **find, int *len_find);
int								backspace_one_sy(char **find, int *len_find,
									int *len);
int								find_in_history(char *find);

/*
** File back_part_hist.c
*/

int								print_new_cmd_from_history(int coincidence);
char							*free_find_hist(char **find);

/*
** ____________________________________________________________________________
*/

/*
** File print_readline_help.c
*/

void							print_help(short flag);
void							print_readline_help(short flag,
									short undo, char *space);
void							print_readline_help_moving_cursor(short flag,
									short undo, char *space);
void							print_readline_help_ccp(short flag,
									short undo, char *space);
void							print_readline_help_other(short flag,
									short undo, char *space);

#endif
