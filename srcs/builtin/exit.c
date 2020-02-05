/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:03:04 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/05 15:24:53 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

int				btin_exit(t_exit_status status)
{
	//TODO чистка parser
	fill_hist_in_file();
	clean_everything();
	ft_putendl_fd("exit", STDOUT_FILENO);
	//TODO функция, по типу atexit баша, с каким статусом завершилась программа
	exit(status);
}
