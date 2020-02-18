/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 19:35:23 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/18 17:26:55 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "parser.h"

/*
** Here we come with the counters of the beginning and the end of the 
** final processes and all the fds defined after redirection block
** Flags are defined also before in the parser block. Here we finish the
** preparation by forming the environ array for execution, forming 
** argc and argv variables
*/

int				before_exec(t_ltree *sub)
{
	char		*add = NULL;
	
	sub->envir = init_exec_environ();
	add_new_to_exec_env(&sub->envir, add);
	//&sub->args_v
	//&sub->args_c
	return (0);
}
