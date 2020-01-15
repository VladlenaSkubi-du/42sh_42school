/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_42.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 20:46:22 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/15 20:49:00 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_42_H
# define LIBFT_42_H

# include <unistd.h>
# include <stdlib.h>

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

void							*ft_realloc(void *subj, size_t len_subj,
								size_t len, size_t len_needed);
void							*ft_xmalloc(size_t size);
void							swap_chars(char *cmd, int b, int a);
void							swap_ints(int *a, int *b);
int								ft_issign(char c);
char							*ft_straddsy(char *dest, char sy);

#endif
