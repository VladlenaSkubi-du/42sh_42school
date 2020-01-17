/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell42.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:38:49 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/17 14:41:37 by sschmele         ###   ########.fr       */
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
# include "readline.h"
# include "builtin42.h"
# include "libft.h"
# include "libft_42.h"

# include "ft_printf.h" //If not used, delete
# include "get_next_line.h" //If not used, delete

/*
** @g_env - global variable with (char **environ) parameters
** @sh_var - shell variables
*/

char				**g_env;
char				**g_shvar;

/*
** File environment42.c
*/

int					save_environment(void);
int					count_first_env(void);
int					save_shell_variables(void);

/*
** File signals_processing42.c
*/

int             	signals_reroute(int from);
void            	sig_readline(int sig);
void                sig_fork(int sig);

/*
** File errors_handler42.c
*/

int             	error_handler(exit_status status, char *str);

/*
** File clean_all42.c
*/

int				    clean_everything(void);
int					clean_readline42(void);

#endif