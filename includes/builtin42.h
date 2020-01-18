/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin42.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:45:45 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/18 18:21:27 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN42_H
# define BUILTIN42_H

# include "exit_status.h"
# include "libft.h"
# include "libft_42.h"
# include "shell42.h"

# include "ft_printf.h" //If not used, delete
# include "get_next_line.h" //If not used, delete

int				btin_exit(t_exit_status status);

#endif