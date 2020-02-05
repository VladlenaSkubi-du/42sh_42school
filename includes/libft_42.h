/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_42.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 20:46:22 by sschmele          #+#    #+#             */
/*   Updated: 2020/02/05 17:09:17 by rbednar          ###   ########.fr       */
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

typedef struct					s_stack
{
    int							data;
    struct s_stack				*next;
}								t_stack;

void							*ft_realloc(void *subj, size_t len_subj,
								size_t len, size_t len_needed);
void							*ft_xmalloc(size_t size);
void							swap_chars(char *cmd, int b, int a);
void							swap_ints(int *a, int *b);
int								ft_issign(char c);
char							*ft_straddsy(char *dest, char sy);
int								ft_strrchri(char *s, int c);
void                            ft_add_list_to_end(t_list **start, t_list *new_list);

/*
** Folder stask_structure______________________________________________________
*/

t_stack							*ft_init_stack(void);
int								ft_pop_stack(t_stack **head);
int								ft_push_stack(t_stack **head, int data);
void							ft_clear_stack(t_stack **head);
int				                ft_last_stack(t_stack **head);

#endif
