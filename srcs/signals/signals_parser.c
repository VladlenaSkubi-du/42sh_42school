/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 13:33:05 by vladlenasku       #+#    #+#             */
/*   Updated: 2020/03/24 14:02:12 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

void				signal_ctrl_c_parser(int sig)
{
	ft_putendl_fd("\nstopped by signal SIGINT", STDOUT_FILENO);
}

void				signal_ctrl_z_parser(int sig)
{
	ft_putendl_fd("\nSIGSTP, to do", STDOUT_FILENO);
}

void				signal_ctrl_bslash_parser(int sig)
{
	ft_putendl_fd("\nSIGQUIT, to do", STDOUT_FILENO);
}

void				signal_ctrl_y_parser(int sig)
{
	ft_putendl_fd("\nSIGCONT, to do", STDOUT_FILENO);
}