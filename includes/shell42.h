/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell42.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 16:09:17 by sschmele          #+#    #+#             */
/*   Updated: 2020/09/01 20:58:27 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL42_H
# define SHELL42_H

# define _DEFAULT_SOURCE 1

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <signal.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/dir.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <grp.h>
# include <sys/xattr.h>
# include <time.h>
# include <pwd.h>
# include <string.h>
# include <stdio.h>

# include "libft.h"
# include "exit_status.h"
# include "parser.h"
# include "readline.h"
# include "jobs.h"
# include "./builtins/builtin42.h"

/*
** Values
** ____________________________________________________________________________
*/

/*
** Values used for shell history
*/

# define HISTORY_LIMIT 32767
# define MAX_HISTFILE 500
# define MAX_HISTBUF 500

/*
** MAXDIR according to POSIX:  _POSIX_PATH_MAX
*/

# define MAXDIR 256

/*
** Value used for function return in some special cases
*/

# define OUT 42
# define BTIN_ERROR	-42

/*
** Values for 42sh program and options
*/

# define OPTIONS_NUM 5
# define FLAG_42SH_C 0x1

/*
** Flags for shell_variables
*/

# define ENV_VIS 0x1
# define SET_VIS 0x2
# define READONLY 0x4

# define HELP_FLAG 0x10000

/*
** Values for shell_variables:
** MAX_EXIT_STATUS is length of exit_status number
** to allocate memory buffer
** ENV_BUFFER is buffer to allocate for @g_envi
*/

# define MAX_EXIT_STATUS 10
# define ENV_BUFFER 17

/*
** Structures
** ____________________________________________________________________________
*/

/*
** @prompt_func is prompt that is valid according to some
** readline and parser analysis
** Can be: main, dquote, heredoc and so on
*/

typedef struct		s_prompt
{
	int				(*prompt_func)(void);
	int				prompt_len_real;
	int				prompt_len;
}					t_prompt;

/*
** @hist is an array with commands (not separated by \n but
** separated as they came to parser)
** @len is the number of lines (commands) in the history
** @last is counter of the last command saved in the history
** @start is a counter from which command from history file we start to
** fill out buffer - not to rewrite the whole buffer to the file but to add
** We need all
*/

typedef struct		s_history
{
	char			**hist;
	int				len;
	int				counter;
	int				last;
	int				start;
	int				last_fc;
}					t_history;

/*
** @BSLASH is "\", @SCOLON is ";", @AND is "&", @DQUOTE is '"',
** @SQUOTE is "'", @OPAREN is "(", @CPAREN is ")", @OBRACKET is "["
** @CBRACKET is "]", @OBRACE is "{", CBRACE is "}", @DOLLAR is "$",
** @TILDA is "~", @PIPE is "|", @GTHAN is ">", @LTHAN is "<",
** @AST is "*", @EQUAL = "=", @ENTER is "\n", @COMENT is "#",
** @BANG is "!", @COLON is ":",
** @GLUE is " " in DQUOTS, @TEXT is quoted symbol, @END_T is end of line
*/

enum				e_techline
{
	WORD_P = 1,
	SPACE,
	BSLASH,
	SCOLON,
	AND,
	DQUOTE,
	SQUOTE,
	OPAREN,
	CPAREN,
	OBRACKET,
	CBRACKET,
	OBRACE,
	CBRACE,
	DOLLAR,
	TILDA,
	PIPE,
	GTHAN,
	LTHAN,
	AST,
	EQUAL,
	ENTER,
	COMENT,
	BANG,
	COLON,
	GLUE,
	TEXT,
	END_T,
	SQUOTE_ANSI,
};

/*
** Globals
** ____________________________________________________________________________
*/

/*
** @g_envi - global variable with all the shell variables
** @g_var_size is the length of the @g_envi buffer
** @g_prompt is the function and the prompt valid
** @g_hist is the structure with the history valid for
** the shell session
*/

char				**g_envi;
int					g_var_size;
t_prompt			g_prompt;
t_history			g_hist;

/*
** Functions
** ____________________________________________________________________________
*/

/*
** File main.c
*/

int					noninteractive_shell(char **argv);
int					interactive_shell(void);
int					preparation_noninteractive(void);

/*
** File options_proc42.c
*/

int					find_options(int num, char *flags_arr[num], char **arr);
int					options_in_arg(char *arri, int num,
						char *flags_arr[num], int *final);
int					options_proc(char arrij, char *flags_arr, int *final);
int					suboptions_proc(char *arri, int num,
						char *flags_arr[num], int *final);

/*
** File options_42sh_42.c
*/

int					check_shell_options(char **argv);
int					check_shell_c_option(char **argv);
int					btin_shell_error_message(char *option, int error);
int					check_shell_script_execution(char *file);
int					execute_shell_file(char *file);

/*
** File signals_processing42.c
*/

int					signals_reroute(int from);
void				signal_ctrl_c_readline(int sig);
void				signal_screen_readline(int sig);
void				signal_ctrl_c_parser(int sig);

/*
** File errors_handler42.c
*/

int					error_handler(int status, char *str);
int					terminal_errors(int status, char *str);
int					error_handler_continuation(int status, char *str);
int					error_handler_files_and_commands(int status, char *str);

/*
** File errors_handler_suberrors.c
*/

int					variable_errors(int status, char *str);
int					options_errors(int status, char *str);
int					syntax_errors(int status, char *str);

/*
** File clean_all42.c
*/

int					clean_everything(void);
int					clean_parser42(void);
int					clean_termcap(void);

/*
** File print_parser_processing.c
*/

void				print_techline(char *cmd,
						char *techline, int len_tech);

/*
** Folder SHELL_VARIABLES
** ____________________________________________________________________________
*/

/*
** File form_environment42.c
*/

int					create_env(void);
int					save_environment_variable(int num);
int					save_shell_variable(int num);
int					exit_status_variables(int status);
int					save_readonly_variable(int num);

/*
** File add_new_value.c
*/

char				*find_env_value(char *str);
int					find_in_variable(int *j, char *name);
int					form_local_envir(char ***arr, int size);
int					add_new_env(char *name);
int					change_env_value(char *new_val, int i);

/*
** File envir_variables.c
*/

int					find_in_any_variable(char **env, int *j, char *name);

/*
** Folder UNIX_FUNCTIONS
**_____________________________________________________________________________
*/

size_t				ft_count_words(char const *s, char c, size_t len);
char				*ft_find_token_sep(char *str);
char				*ft_make_techline(char *cmd, int len);
char				get_tech_num(char check);
char				*ft_home_from_etcpasswd(void);

#endif
