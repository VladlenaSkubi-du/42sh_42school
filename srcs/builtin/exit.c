/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:03:04 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/12 18:04:34 by rbednar          ###   ########.fr       */
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
