
#ifndef SHELL42_H
# define SHELL42_H

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
# include "./builtins/builtin42.h"
# include "jobs.h"

/*
** Values
** ____________________________________________________________________________
*/

/*
** Values used for shell history
*/

# define			HISTORY_LIMIT 32767
# define 			MAX_HISTFILE 500
# define 			MAX_HISTBUF 500

/*
** MAXDIR according to POSIX:  _POSIX_PATH_MAX
*/

# define			MAXDIR 256

/*
** Value used for function return in some special cases
*/

# define			OUT 42

/*
** Values for 42sh program and options
*/

# define			OPTIONS_NUM		5
# define			FLAG_42SH_C		0x1

/*
** Flags for shell_variables
*/

# define			ENV_VIS		0x1
# define			SET_VIS		0x2
# define			READONLY 	0x4

/*
** Values for shell_variables:
** MAX_EXIT_STATUS is length of exit_status number
** to allocate memory buffer
** ENV_BUFFER is buffer to allocate for @g_envi
*/

# define			MAX_EXIT_STATUS 10
# define 			ENV_BUFFER 100

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
	SPACE ,
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

char				**g_env; //DIMA delete
char				**g_rdovar; //DIMA delete
char				**g_shvar; //DIMA delete
char				**g_lovar; //DIMA delete
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

int					check_42sh_options(int argc, char **argv);
int					check_42sh_c_option(int argc, char **argv);
int					invalid_option_42sh(char *option, char *name);
int					argument_needed_42sh(char *option, char *name);

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
int					error_handler_continuation(int status, char *str);
int					variable_errors(int status, char *str);
int					options_errors(int status, char *str);
int					syntax_errors(int status, char *str);
int					syntax_errors_files(int status, char *str);

/*
** File clean_all42.c
*/

int					clean_everything(void);
int					clean_readline42(void);
int					clean_parser42(void);
int					clean_termcap(void);

/*
** Folder SHELL_VARIABLES
** ____________________________________________________________________________
*/

// OLD

int					save_readonly_variables(void);
int					save_shell_variables(void);
int					save_environment_variables(void);
int					save_local_variables(void);
int					realloc_all_gvariables_array(void);
size_t				find_in_variables(char **arr, size_t *j, char *name);
char				**init_exec_environ(void);
int					insert_assign_to_arrays(char *find, char *insert,
						char **array);
int					if_noninteractive(void);
int					add_to_environment_variables(char *add);
int					add_to_local_variables(char *add);
int					add_new_to_exec_env(char ***array, char **add);
int					unset_from_array(char ***arr, int i);
int					clean_in_shvar_array(char ***arr, int i, int j);
int					exit_status_variable(int status);

// NEW

int					create_env(void);
char				*find_env_value(char *str);
int					find_in_variable(int *j, char *name);
int					form_local_envir(char ***arr, int size);
int					add_new_env(char *name);
int					change_env_value(char *new_val, int i);
int					save_shell_variable(int num);
int					save_environment_variable(int num);
int					save_readonly_variable(void);
int					exit_status_variables(int status);



/*
** Folder UNIX_FUNCTIONS
**_____________________________________________________________________________
*/

size_t				ft_count_words(char const *s, char c, size_t len);
char				*ft_find_token_sep(char *str);
char				*ft_make_techline(char *cmd, int len);
char				get_tech_num(char check);

#endif
