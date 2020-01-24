/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_42.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 20:46:22 by sschmele          #+#    #+#             */
/*   Updated: 2020/01/24 12:59:57 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_42_H
# define LIBFT_42_H

# include <unistd.h>
# include <stdlib.h>

# include "exit_status.h"
# include "libft.h"

# include "ft_printf.h" //If not used, delete
# include "get_next_line.h" //If not used, delete

void							*ft_realloc(void *subj, size_t len_subj,
								size_t len, size_t len_needed);
void							*ft_xmalloc(size_t size);
void							swap_chars(char *cmd, int b, int a);
void							swap_ints(int *a, int *b);
int								ft_issign(char c);
char							*ft_straddsy(char *dest, char sy);
int								ft_strrchri(char *s, int c);

#endif
