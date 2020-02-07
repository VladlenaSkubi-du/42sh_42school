/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:03:04 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/07 21:52:49 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

int				btin_exit(t_exit_status status)
{
	//TODO чистка парсер
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (fill_hist_in_file())
	{
		clean_everything();
		error_handler(HISTORY_FILE_FAIL, NULL);
		exit(HISTORY_FILE_FAIL);
	}
	clean_everything();
	//TODO функция, по типу atexit баша, с каким статусом завершилась программа
	exit(status);
}
