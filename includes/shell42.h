/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell42.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:38:49 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/30 15:16:16 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL42_H
# define SHELL42_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <signal.h>

// # include <stdio.h> //DELETE

# include "exit_status.h"
# include "builtin42.h"
# include "libft.h"
# include "libft_42.h"
# include "parser.h"
# include "readline.h"

# include "ft_printf.h" //If not used, delete
# include "get_next_line.h" //If not used, delete

typedef struct		s_prompt
{
	int				(*prompt_func)(void);
}					t_prompt;

/*
** @SLASH is "\", @SCOLON is ";", @AND is "&", @DQUOTE is '"',
** @SQUOTE is "'", @OPAREN is "(", @CPAREN is ")", @OBRACKET is "["
** @CBRACKET is "]", @OBRACE is "{", CBRACE is "}", @DOLLAR is "$",
** @TILDA is "~", @PIPE is "|", @GTHAN is ">", @LTHAN is "<",
** @AST is "*", @EQUAL = "=", @ENTER is "\n"
*/

enum				e_techline
{
	SPACE = 1,
	SLASH,
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
	ENTER
}					t_sign_techline;

/*
** @g_env - global variable with (char **environ) parameters
** @g_sh_var - shell variables
*/

char				**g_env;
char				**g_shvar;
t_prompt			g_prompt;

/*
** File environment42.c
*/

int					save_environment(void);
int					count_first_env(void);
int					save_shell_variables(void);

/*
** File signals_processing42.c
*/

int					signal_ctrl_c(void);
int					signals_reroute(int from);
void				sig_readline(int sig);
void				sig_fork(int sig);

/*
** File errors_handler42.c
*/

int					error_handler(t_exit_status status, char *str);

/*
** File clean_all42.c
*/

int					clean_everything(void);
int					clean_readline42(void);
int					clean_parser42(void);

#endif
