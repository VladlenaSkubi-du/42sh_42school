/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:03:04 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/24 13:31:50 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

int				btin_exit(t_exit_status status)
{
	reset_canonical_input();
	clean_readline42();
	//TODO чистка parser
	clean_everything();
	//TODO буфер истории записывается в файл
	ft_putendl_fd("exit", STDOUT_FILENO);
	//TODO функция, по типу atexit баша, с каким статусом завершилась программа
	exit(status);
}
