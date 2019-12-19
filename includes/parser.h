/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 15:04:04 by hshawand          #+#    #+#             */
/*   Updated: 2019/12/20 00:06:27 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include <unistd.h>

/*
** Struct to save and work with techline
*/
typedef struct  s_tech
{
   char			*line;
   size_t		len;    
}               t_tech;

typedef struct  s_ltree
{
	size_t		start; //index of start
	size_t		end;
}               t_ltree;

/*
**Global vars
*/

char	*g_cmd;
size_t	g_cmd_size;
t_tech	*g_techline;

/*
** File pareser.c
*/

int		parser(char *line);

/*
** File quote_control.c
*/

int		nullify(void);

/*
** File brackets.c
*/

int		ft_brackets(char *str, int end);

/*
** File slice_to_blocks.c
*/

int 	ft_block_start_fg(t_ltree *block);
int		ft_block_start_bg(t_ltree *block);
int     ft_slice(void);

/*
** File find_spec.c
*/

t_ltree		*ft_find_spec(t_ltree *block);

#endif