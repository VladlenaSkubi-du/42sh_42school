/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:03:04 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/12 19:08:06 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

int				btin_exit(int status)
{
	//TODO чистка парсер
	ft_putendl_fd("exit", STDOUT_FILENO);
	fill_hist_in_file();
	clean_everything();
	//TODO функция, по типу atexit баша, с каким статусом завершилась программа
	exit(status);
}
