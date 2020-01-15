/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell42.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:38:49 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/15 20:46:04 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL42_H
# define SHELL42_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <signal.h>

# include <stdio.h> //DELETE

# include "libft.h"
# include "libft_42.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "readline.h"

/*
** @g_env - global variable with (char **environ) parameters
** @sh_var - shell variables
*/

char				**g_env;
char				**g_shvar;

/*
** File 42environment.c
*/

int					save_environment(void);
int					count_first_env(void);
int					save_shell_variables(void);
int					clean_everything(void);

/*
** File 42signals_processing.c
*/

int             	signals_reroute(void);
void            	signal_handler(int sig);

#endif